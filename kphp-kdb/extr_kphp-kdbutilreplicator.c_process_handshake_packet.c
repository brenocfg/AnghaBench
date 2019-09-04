#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct repl_server_status {int flags; long long client_log_recvpos; long long client_log_wrpos; long long client_log_pos; long long buffer_file_pos; int logrotate_pos; TYPE_2__* binlog; int /*<<< orphan*/  buffer; int /*<<< orphan*/  wptr; int /*<<< orphan*/  rptr; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  conn_generation; struct connection* conn; int /*<<< orphan*/  handshake_id; struct related_binlog* rb; struct repl_server_status* server_next; struct repl_server_status* server_prev; } ;
struct repl_handshake_ok {int session_id; long long binlog_slice_start_pos; long long binlog_slice_end_pos; long long binlog_last_start_pos; int /*<<< orphan*/  binlog_last_end_pos; int /*<<< orphan*/  handshake_id; int /*<<< orphan*/  type; } ;
struct repl_handshake {scalar_t__ type; int binlog_tag_len; int binlog_slice_name_len; char* binlog_tag; char* binlog_slice_name; int binlog_file_size; scalar_t__ binlog_slice_start_pos; scalar_t__ binlog_slice_end_pos; int binlog_first_file_size; int /*<<< orphan*/  handshake_id; int /*<<< orphan*/  binlog_file_end_hash; int /*<<< orphan*/  binlog_file_start_hash; int /*<<< orphan*/  binlog_first_file_start_hash; } ;
struct remote_binlog {int dummy; } ;
struct related_binlog {int flags; scalar_t__ update_generation; int first_file_start_size; char* path; long long slice_binlog_pos; int /*<<< orphan*/  max_binlog_pos; struct repl_server_status* server_last; TYPE_4__* kfs_replica; int /*<<< orphan*/  first_file_start_hash; scalar_t__ min_binlog_pos; struct remote_binlog* binlog; } ;
struct connection {int /*<<< orphan*/  remote_port; int /*<<< orphan*/  generation; } ;
typedef  int /*<<< orphan*/  md5_hash_t ;
typedef  TYPE_2__* kfs_file_handle_t ;
struct TYPE_10__ {scalar_t__ file_size; } ;
struct TYPE_9__ {TYPE_5__** binlogs; } ;
struct TYPE_8__ {int fd; TYPE_1__* info; } ;
struct TYPE_7__ {int flags; long long log_pos; long long file_size; int kfs_headers; char* filename; } ;

/* Variables and functions */
 struct related_binlog* LR ; 
 int LRF_BROKEN ; 
 int LRF_MASTER ; 
 scalar_t__ P_REPL_HANDSHAKE ; 
 int /*<<< orphan*/  P_REPL_HANDSHAKE_OK ; 
 int RS_LOADDISK ; 
 int RS_LOGROTATE ; 
 int RS_REPL_STARTED ; 
 int RS_ZEROSTART ; 
 int RS_ZIPPED ; 
 int /*<<< orphan*/  R_ERROR_EBADSLICE ; 
 int /*<<< orphan*/  R_ERROR_EINVAL ; 
 int /*<<< orphan*/  R_ERROR_ENOENT ; 
 int /*<<< orphan*/  R_ERROR_EUNLINKSLICE ; 
 int /*<<< orphan*/  SEND_BUFFER_SIZE ; 
 struct repl_handshake_ok* alloc_packet (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close_binlog (TYPE_2__*,int) ; 
 int /*<<< orphan*/  compute_start_end_hashes (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_orig_file_size (TYPE_5__*) ; 
 struct remote_binlog* get_rb_hash (char*,int,int /*<<< orphan*/ ) ; 
 struct repl_server_status* get_server_by_session (int,int) ; 
 int last_session_id ; 
 int local_rbs ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md5 (unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * memchr (char*,char,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_unlink_slice ; 
 TYPE_2__* open_binlog (TYPE_4__*,scalar_t__) ; 
 int pread (int,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_packet (struct connection*,int) ; 
 int send_error (struct connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  show_remote_ip (struct connection*) ; 
 scalar_t__ sigrtmax_cnt ; 
 scalar_t__ stats_buff ; 
 int /*<<< orphan*/  stderr ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  update_related_binlog (struct related_binlog*) ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int zipped_filename (char*) ; 

int process_handshake_packet (struct connection *c, struct repl_handshake *HS, int len) {
  int S_flags;
  assert (HS->type == P_REPL_HANDSHAKE && len >= sizeof (struct repl_handshake));
  if ((unsigned) HS->binlog_tag_len >= 1024 || (unsigned) HS->binlog_slice_name_len >= 1024) {
    return send_error (c, HS->handshake_id, 0, R_ERROR_EINVAL, "bad handshake packet: strings longer than 1024 bytes");
  }
  if (((HS->binlog_tag_len + HS->binlog_slice_name_len + 2 + sizeof (struct repl_handshake) + 3) & -4) != len) {
    return send_error (c, HS->handshake_id, 0, R_ERROR_EINVAL, "bad handshake packet: incorrect total packet size");
  }
  if (HS->binlog_tag[HS->binlog_tag_len] || HS->binlog_slice_name[HS->binlog_tag_len + 1 + HS->binlog_slice_name_len]) {
    return send_error (c, HS->handshake_id, 0, R_ERROR_EINVAL, "bad handshake packet: strings are not zero-terminated");
  }
  char *client_slice_name = HS->binlog_slice_name + HS->binlog_tag_len + 1;
  vkprintf (2, "received handshake packet from %s:%d, handshake_id=%d, for binlog tag %s, slice name %s (size %lld, pos %lld..%lld)\n", show_remote_ip (c), c->remote_port, HS->handshake_id, HS->binlog_tag, client_slice_name, HS->binlog_file_size, HS->binlog_slice_start_pos, HS->binlog_slice_end_pos);
  struct remote_binlog *remb = get_rb_hash (HS->binlog_tag, HS->binlog_tag_len, 0);
  if (!remb) {
    return send_error (c, HS->handshake_id, 0, R_ERROR_ENOENT, "we don't know anything about requested binlog tag");
  }
  int i;
  struct related_binlog *R = 0;
  for (i = 0; i < local_rbs; i++) {
    if (LR[i].binlog == remb) {
      R = &LR[i];
    }
  }
  if (!R) {
    return send_error (c, HS->handshake_id, 0, R_ERROR_ENOENT, "no copies of requested binlog are present here");
  }
  if ((R->flags & LRF_BROKEN) != 0) {
    return send_error (c, HS->handshake_id, 0, R_ERROR_ENOENT, "local copy of requested binlog is broken");
  }
  if (!(R->flags & LRF_MASTER)) {  // is this check really necessary?
    return send_error (c, HS->handshake_id, 0, R_ERROR_ENOENT, "don't have master copy of requested binlog");
  }

  if (!HS->binlog_slice_name_len) {
    if (HS->binlog_first_file_size != -1 || HS->binlog_file_size != -1 || HS->binlog_slice_start_pos != 0 || HS->binlog_slice_end_pos != 0) {
      return send_error (c, HS->handshake_id, 0, R_ERROR_EINVAL, "no slice name passed but binlog files exist at client or log position is non-zero");
    }
    if (verbosity > 0) {
      fprintf (stderr, "client requested replication of %s without initial files\n", HS->binlog_tag);
    }
    if (R->min_binlog_pos) {
      return send_error (c, HS->handshake_id, 0, R_ERROR_ENOENT, "replication from position 0 is impossible : binlog start slice not found on server");
    }
  } else {
    if (HS->binlog_file_size <= 0) {
      return send_error (c, HS->handshake_id, 0, R_ERROR_EINVAL, "last binlog slice cannot be empty");
    }
    if (!(HS->binlog_slice_start_pos >= 0 && HS->binlog_slice_end_pos >= 0 && HS->binlog_file_size >= HS->binlog_slice_end_pos - HS->binlog_slice_start_pos)) {
      return send_error (c, HS->handshake_id, 0, R_ERROR_EINVAL, "impossible binlog slice start/end log positions");
    }
  }

  if ((HS->binlog_first_file_size >= 0 && !R->min_binlog_pos && HS->binlog_first_file_size > R->kfs_replica->binlogs[0]->file_size) || R->update_generation != sigrtmax_cnt) {
    update_related_binlog (R);
  }

  if (HS->binlog_first_file_size >= 0) {
    kfs_file_handle_t binlog = 0;
    if (!R->min_binlog_pos) {
      int start_size = (HS->binlog_first_file_size < (1 << 20) ? HS->binlog_first_file_size : (1 << 20));
      if (HS->binlog_first_file_size > get_orig_file_size (R->kfs_replica->binlogs[0])) {
        return send_error (c, HS->handshake_id, 0, R_ERROR_EBADSLICE, "first binlog file is longer at slave than at master");
      }
      const int has_tag = memchr (HS->binlog_tag, '@', HS->binlog_tag_len) != NULL;
      if (start_size == R->first_file_start_size || has_tag) {
        binlog = (void *) -1;
        if (memcmp (HS->binlog_first_file_start_hash, R->first_file_start_hash, sizeof (md5_hash_t))) {
          return send_error (c, HS->handshake_id, 0, R_ERROR_EBADSLICE, "first binlog file hash mismatch");
        } else if (verbosity > 0) {
          if (has_tag) {
            fprintf (stderr, "first binlog file tag check passed\n");
          } else {
            fprintf (stderr, "first binlog file prefix check passed (%d first bytes checked)\n", start_size);
          }
        }
      } else {
        assert (start_size < R->first_file_start_size);
        binlog = open_binlog (R->kfs_replica, 0);
        if (binlog) {
          assert (!(binlog->info->flags & 16)); /* why we pack first binlog if it's original size is lesser than 1m? */ 
          int fd = binlog->fd;
          static md5_hash_t start_hash;
          assert (pread (fd, stats_buff, start_size, 0) == start_size);
          close_binlog (binlog, 1);
          md5 ((unsigned char *) stats_buff, start_size, start_hash);
          if (memcmp (HS->binlog_first_file_start_hash, start_hash, sizeof (md5_hash_t))) {
            return send_error (c, HS->handshake_id, 0, R_ERROR_EBADSLICE, "first binlog file hash mismatch");
          } else if (verbosity > 0) {
            fprintf (stderr, "first binlog file prefix check passed (%d first bytes checked)\n", start_size);
          }
        }
      }
    }
    if (!binlog) {
      fprintf (stderr, "warning: cannot check hash of first binlog for %s\n", R->path);
    }
  } else {
    if (HS->binlog_first_file_size != -1 || (HS->binlog_slice_start_pos <= 0 && HS->binlog_file_size >= 0)) {
      return send_error (c, HS->handshake_id, 0, R_ERROR_EINVAL, "received invalid first file size");
    }
  }

  assert (HS->binlog_slice_start_pos >= 0);

  kfs_file_handle_t binlog = open_binlog (R->kfs_replica, HS->binlog_slice_start_pos);
  if (!binlog) {
    return send_error (c, HS->handshake_id, 0, R_ERROR_ENOENT, "cannot start replication from binlog position requested by client: binlog slice absent on server");
  }

  long long binlog_start_pos = binlog->info->log_pos;
  long long binlog_end_pos = binlog_start_pos + binlog->info->file_size - 4096 * binlog->info->kfs_headers;
  if (verbosity > 0) {
    fprintf (stderr, "opening local slice %s (covering %lld..%lld)\n", binlog->info->filename, binlog_start_pos, binlog_end_pos);
  }

  if (binlog_start_pos != HS->binlog_slice_start_pos) {
    return send_error (c, HS->handshake_id, 0, R_ERROR_EBADSLICE, "client binlog slice start position does not match master");
  }

  const int server_zipped = zipped_filename (binlog->info->filename);
  assert (server_zipped >= 0);

  if (HS->binlog_file_size >= 0) {
    const int client_zipped = zipped_filename (client_slice_name);
    if (client_zipped < 0) {
      return send_error (c, HS->handshake_id, 0, R_ERROR_EBADSLICE, "bad slice suffix");
    }

    if (server_zipped != client_zipped) {
      return server_zipped ?
        send_error (c, HS->handshake_id, 0, R_ERROR_EUNLINKSLICE, "%s%s", msg_unlink_slice, client_slice_name) :
        send_error (c, HS->handshake_id, 0, R_ERROR_EBADSLICE, "client has zipped slice, but server has original slice");
    }

    if (binlog_end_pos < HS->binlog_slice_end_pos) {
      return send_error (c, HS->handshake_id, 0, R_ERROR_EBADSLICE, "client binlog slice is longer than at master");
    }
    if (binlog_end_pos - 36 < HS->binlog_slice_end_pos && HS->binlog_slice_end_pos < binlog_end_pos && R->slice_binlog_pos > binlog_start_pos) {
      return send_error (c, HS->handshake_id, 0, R_ERROR_EBADSLICE, "client binlog slice trailing LEV_ROTATE_TO record is truncated");
    }
    if (binlog->info->kfs_headers * 4096 != HS->binlog_file_size - (HS->binlog_slice_end_pos - HS->binlog_slice_start_pos)) {
      return send_error (c, HS->handshake_id, 0, R_ERROR_EBADSLICE, "client and master binlog slice kfs headers are of different size");
    }
    char *local_slice_name = binlog->info->filename;
    char *ptr = strrchr (local_slice_name, '/');
    if (ptr) {
      local_slice_name = ptr + 1;
    }
    /* useless check TODO: check its uselessness
       if (strcmp (local_slice_name, client_slice_name)) {
       return send_error (c, HS->handshake_id, 0, R_ERROR_EBADSLICE, "client and master binlog slice names differ");
       }
     */
    static md5_hash_t start_hash, end_hash;
    compute_start_end_hashes (binlog->fd, HS->binlog_file_size, start_hash, end_hash);
    if (memcmp (HS->binlog_file_start_hash, start_hash, sizeof (md5_hash_t))) {
      return send_error (c, HS->handshake_id, 0, R_ERROR_EBADSLICE, "client and master binlog slice start hashes differ");
    }
    if (memcmp (HS->binlog_file_end_hash, end_hash, sizeof (md5_hash_t))) {
      return send_error (c, HS->handshake_id, 0, R_ERROR_EBADSLICE, "client and master binlog slice end hashes differ, client file is not a prefix of master copy");
    }
    if (verbosity > 0) {
      fprintf (stderr, "remote binlog slice of length %lld appears to be prefix of local binlog slice %s of length %lld\n", HS->binlog_file_size, local_slice_name, binlog->info->file_size);
    }
    // close_binlog (binlog, 1);
    S_flags = RS_REPL_STARTED;
    // here: start replication
    int n = 36;
    if (server_zipped) {
      S_flags |= RS_ZIPPED;
      n = 0;
    }
    if (binlog_end_pos - n <= HS->binlog_slice_end_pos && R->slice_binlog_pos > binlog_start_pos) {
      S_flags |= RS_LOGROTATE;
    }
  } else {
    S_flags = RS_REPL_STARTED | RS_ZEROSTART | RS_LOGROTATE;
    // here: start replication from empty set of files
  }

  if (verbosity > 0) {
    fprintf (stderr, "handshake: all sanity checks passed!\n");
  }

  int session_id = (++last_session_id & 0x3fffffff) + 1;
  assert (!get_server_by_session (session_id, 0));
  struct repl_server_status *S = get_server_by_session (session_id, 1);

  S->server_prev = R->server_last;
  S->server_next = (struct repl_server_status *) R;
  R->server_last->server_next = S;
  R->server_last = S;

  S->rb = R;
  S->handshake_id = HS->handshake_id;
  S->flags = 0;
  S->conn = c;
  S->conn_generation = c->generation;

  //S->client_file_size = HS->binlog_file_size;
  S->client_log_recvpos = S->client_log_wrpos = S->client_log_pos = HS->binlog_slice_end_pos;

  S->buffer_size = SEND_BUFFER_SIZE;
  S->buffer = malloc (S->buffer_size);
  S->rptr = S->wptr = S->buffer;
  S->flags = S_flags;
  if (!(S->flags & RS_ZEROSTART)) {
    S->flags |= RS_LOADDISK;
    S->buffer_file_pos = S->client_log_pos - binlog_start_pos + binlog->info->kfs_headers * 4096;
    S->logrotate_pos = -1;
    S->binlog = binlog;
    if (S->flags & RS_LOGROTATE) {
      S->logrotate_pos = HS->binlog_slice_end_pos;
    }
  } else {
    close_binlog (binlog, 1);
    S->buffer_file_pos = 0;
    S->logrotate_pos = 0;
    S->binlog = 0;
  }

  struct repl_handshake_ok *HO = alloc_packet (sizeof (struct repl_handshake_ok));
  HO->type = P_REPL_HANDSHAKE_OK;
  HO->handshake_id = HS->handshake_id;
  HO->session_id = session_id;
  HO->binlog_slice_start_pos = binlog_start_pos;
  HO->binlog_slice_end_pos = binlog_end_pos;
  HO->binlog_last_start_pos = R->slice_binlog_pos;
  HO->binlog_last_end_pos = R->max_binlog_pos;

  vkprintf (2, "acknowledging handshake to %s:%d, session=%d:%d, for binlog tag %s, current slice pos %lld..%lld, last slice pos %lld..%lld\n", show_remote_ip (c), c->remote_port, HO->handshake_id, session_id, HS->binlog_tag, HO->binlog_slice_start_pos, HO->binlog_slice_end_pos, HO->binlog_last_start_pos, HO->binlog_last_end_pos);

  push_packet (c, sizeof (struct repl_handshake_ok));

  return 0;
}