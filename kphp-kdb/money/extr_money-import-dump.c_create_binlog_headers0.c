#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int raw_size; int total_copies; int schema_id; int extra_bytes; int split_mod; int split_min; int /*<<< orphan*/  split_max; int /*<<< orphan*/  schema_extra; int /*<<< orphan*/  slice_creator; int /*<<< orphan*/  creator; int /*<<< orphan*/  modified; int /*<<< orphan*/  created; int /*<<< orphan*/  slice_created; int /*<<< orphan*/  replica_created; int /*<<< orphan*/  slice_name; int /*<<< orphan*/  table_name; int /*<<< orphan*/  table_id_hash; void* slice_id_hash; void* replica_id_hash; void* file_id_hash; int /*<<< orphan*/  header_seq_num; int /*<<< orphan*/  kfs_file_type; } ;

/* Variables and functions */
 TYPE_1__* KHDR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int binlog_headers ; 
 int /*<<< orphan*/  create_kfs_header_basic (TYPE_1__*) ; 
 char* default_progname ; 
 int /*<<< orphan*/  fix_kfs_header_crc32 (TYPE_1__*) ; 
 TYPE_1__* kfs_Hdr ; 
 int /*<<< orphan*/  kfs_binlog ; 
 void* kfs_random_hash () ; 
 int /*<<< orphan*/  kfs_string_hash (char*) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  split_max ; 
 int split_min ; 
 int split_mod ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ stdout_mode ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  targ_fd ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

void create_binlog_headers0 (int schema_id, char *schema_str) {
  assert (!binlog_headers && !KHDR);

  if (stdout_mode) {
    return;
  }

  binlog_headers = 2;
  create_kfs_header_basic (kfs_Hdr);

  KHDR = kfs_Hdr;

  KHDR->kfs_file_type = kfs_binlog;
  KHDR->modified = time (0);
  KHDR->header_seq_num++;

  KHDR->file_id_hash = kfs_random_hash ();
  KHDR->replica_id_hash = KHDR->slice_id_hash = kfs_random_hash ();

  KHDR->table_id_hash = kfs_string_hash ("money");
  strcpy (KHDR->table_name, "money");
  if (split_mod > 1) {
    sprintf (KHDR->slice_name, "money%03d", split_min);
  } else {
    strcpy (KHDR->slice_name, "money");
  }

  KHDR->raw_size = 8192;
  KHDR->replica_created = KHDR->slice_created = KHDR->created = KHDR->modified;

  KHDR->total_copies = 1;

  strcpy (KHDR->creator, default_progname);
  strcpy (KHDR->slice_creator, default_progname);

  KHDR->schema_id = schema_id;
  if (schema_str) {
    KHDR->extra_bytes = strlen (schema_str);
    if (KHDR->extra_bytes > 512) {
      KHDR->extra_bytes = 512;
    }
    memcpy (KHDR->schema_extra, schema_str, KHDR->extra_bytes);
  }

  KHDR->split_mod = split_mod;
  KHDR->split_min = split_min;
  KHDR->split_max = split_max;

  fix_kfs_header_crc32 (KHDR);

  assert (lseek (targ_fd, 0, SEEK_SET) == 0);
  assert (write (targ_fd, kfs_Hdr, 4096) == 4096);
  assert (write (targ_fd, kfs_Hdr, 4096) == 4096);
}