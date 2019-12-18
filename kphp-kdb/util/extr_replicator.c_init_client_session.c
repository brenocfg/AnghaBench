#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct repl_handshake {int handshake_id; int binlog_file_size; int binlog_first_file_size; int binlog_tag_len; int binlog_slice_name_len; int /*<<< orphan*/  binlog_slice_end_pos; int /*<<< orphan*/  binlog_slice_start_pos; scalar_t__* binlog_tag; int /*<<< orphan*/  binlog_file_end_hash; int /*<<< orphan*/  binlog_file_start_hash; scalar_t__* binlog_first_file_start_hash; scalar_t__ flags; int /*<<< orphan*/  type; } ;
struct repl_client_status {int /*<<< orphan*/  conn_generation; struct connection* conn; struct related_binlog* rb; } ;
struct related_binlog {int first_file_start_size; char first_file_start_hash; TYPE_3__* binlog; TYPE_2__* kfs_binlog; TYPE_1__* kfs_replica; int /*<<< orphan*/  min_binlog_pos; int /*<<< orphan*/  max_binlog_pos; int /*<<< orphan*/  slice_binlog_pos; struct repl_client_status** client; } ;
struct kfs_file_info {char* filename; int file_size; } ;
struct connection {int /*<<< orphan*/  remote_port; int /*<<< orphan*/  generation; } ;
typedef  int /*<<< orphan*/  md5_hash_t ;
struct TYPE_6__ {int binlog_tag_len; char* binlog_tag; } ;
struct TYPE_5__ {int /*<<< orphan*/  fd; struct kfs_file_info* info; } ;
struct TYPE_4__ {int /*<<< orphan*/ * binlogs; scalar_t__ binlog_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_REPL_HANDSHAKE ; 
 struct repl_handshake* alloc_packet (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  compute_start_end_hashes (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,struct repl_client_status*,int) ; 
 struct repl_client_status* get_client_by_handshake (int,int) ; 
 int get_orig_file_size (int /*<<< orphan*/ ) ; 
 int last_handshake_id ; 
 scalar_t__ load_binlog_data (struct related_binlog*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  push_packet (struct connection*,int) ; 
 int /*<<< orphan*/  show_remote_ip (struct connection*) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int init_client_session (struct related_binlog *R, struct connection *c, int target_no) {
  assert (!R->client[target_no]);
  int handshake_id = (++last_handshake_id & 0x3fffffff) + 1;
  assert (!get_client_by_handshake (handshake_id, 0));
  struct repl_client_status *C = R->client[target_no] = get_client_by_handshake (handshake_id, 1);
  C->rb = R;
  C->conn = c;
  C->conn_generation = c->generation;
  if (verbosity > 0) {
    fprintf (stderr, "sending handshake to client %p, handshake_id=%d\n", C, handshake_id);
  }
  assert ((R->kfs_binlog && R->kfs_replica->binlog_num) || (!R->kfs_binlog && !R->kfs_replica->binlog_num));
  int binlog_tag_len = R->binlog->binlog_tag_len;
  char *binlog_slice_name = R->kfs_binlog ? R->kfs_binlog->info->filename : "";
  int binlog_slice_name_len = 0;
  if (binlog_slice_name) {
    char *ptr = strrchr (binlog_slice_name, '/');
    if (ptr) {
      binlog_slice_name = ptr + 1;
    }
    binlog_slice_name_len = strlen (binlog_slice_name);
  }
  if (!R->min_binlog_pos && R->kfs_replica->binlog_num) {
    assert (load_binlog_data (R) >= 0);
  }
  struct kfs_file_info *FI = R->kfs_binlog ? R->kfs_binlog->info : 0;
  int rec_size = sizeof (struct repl_handshake) + binlog_tag_len + binlog_slice_name_len + 2;

  struct repl_handshake *HS = alloc_packet (rec_size);
  HS->type = P_REPL_HANDSHAKE;
  HS->handshake_id = handshake_id;
  HS->flags = 0;
  HS->binlog_slice_start_pos = R->slice_binlog_pos;
  HS->binlog_slice_end_pos = R->max_binlog_pos;
  HS->binlog_file_size = FI ? FI->file_size : -1;
  HS->binlog_first_file_size = !R->min_binlog_pos && R->kfs_replica->binlog_num ? get_orig_file_size (R->kfs_replica->binlogs[0]) : -1;
  int start_bytes = HS->binlog_first_file_size < (1L << 20) ? HS->binlog_first_file_size : (1L << 20);
  assert (start_bytes == R->first_file_start_size);
  memcpy (HS->binlog_first_file_start_hash, &R->first_file_start_hash, sizeof (md5_hash_t));
  if (!FI) {
    memset (HS->binlog_file_start_hash, 0, sizeof (md5_hash_t));
    memset (HS->binlog_file_end_hash, 0, sizeof (md5_hash_t));
  } else {
    compute_start_end_hashes (R->kfs_binlog->fd, FI->file_size, HS->binlog_file_start_hash, HS->binlog_file_end_hash);
  }
  HS->binlog_tag_len = binlog_tag_len;
  HS->binlog_slice_name_len = binlog_slice_name_len;
  memcpy (HS->binlog_tag, R->binlog->binlog_tag, binlog_tag_len);
  HS->binlog_tag[binlog_tag_len] = 0;
  memcpy (HS->binlog_tag + binlog_tag_len + 1, binlog_slice_name, binlog_slice_name_len);
  HS->binlog_tag[binlog_tag_len + 1 + binlog_slice_name_len] = 0;

  vkprintf (2, "sending handshake packet to %s:%d, handshake_id=%d, for binlog tag %s, slice name %s (size %lld, pos %lld..%lld)\n", show_remote_ip (c), c->remote_port, HS->handshake_id, HS->binlog_tag, binlog_slice_name, HS->binlog_file_size, HS->binlog_slice_start_pos, HS->binlog_slice_end_pos);

  push_packet (c, rec_size);

  return 0;
}