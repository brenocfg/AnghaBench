#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct lev_start {int type; scalar_t__ schema_id; scalar_t__ split_min; scalar_t__ split_max; scalar_t__ split_mod; } ;
struct lev_rotate_from {scalar_t__ cur_log_pos; scalar_t__ prev_log_hash; } ;
struct kfs_file_header {int dummy; } ;
struct TYPE_7__ {scalar_t__ magic; scalar_t__ kfs_file_type; scalar_t__ header_seq_num; scalar_t__ data_size; scalar_t__ raw_size; int finished; scalar_t__ schema_id; scalar_t__ split_min; scalar_t__ split_max; scalar_t__ split_mod; scalar_t__ log_pos; scalar_t__ prev_log_hash; int /*<<< orphan*/  data_crc32; } ;

/* Variables and functions */
 struct lev_rotate_from* CONT ; 
 scalar_t__ KFS_MAGIC ; 
 TYPE_1__* KHDR ; 
#define  LEV_ROTATE_FROM 129 
#define  LEV_START 128 
 int /*<<< orphan*/  SEEK_END ; 
 struct lev_start* ST ; 
 int /*<<< orphan*/  assert (int) ; 
 int binlog_existed ; 
 int binlog_headers ; 
 scalar_t__ check_kfs_header_basic (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* kfs_Hdr ; 
 scalar_t__ kfs_binlog ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (TYPE_1__*,TYPE_1__*,int) ; 
 int read (int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tot_crc32 ; 

int load_binlog_headers (int fd) {
  int r = read (fd, kfs_Hdr, 4096 * 3);
  struct lev_start *E;
  assert (sizeof (struct kfs_file_header) == 4096);
  binlog_headers = 0;
  binlog_existed = 0;
  ST = 0;
  CONT = 0;
  KHDR = 0;
  if (!r) {
    return 0;
  }
  if (r >= 4096 && kfs_Hdr[0].magic == KFS_MAGIC) {
    if (check_kfs_header_basic (kfs_Hdr) < 0 || kfs_Hdr[0].kfs_file_type != kfs_binlog) {
      fprintf (stderr, "bad kfs header #0\n");
      return -1;
    }
    binlog_headers++;
    if (r >= 8192 && kfs_Hdr[1].magic == KFS_MAGIC) {
      if (check_kfs_header_basic (kfs_Hdr + 1) < 0 || kfs_Hdr[1].kfs_file_type != kfs_binlog) {
        fprintf (stderr, "bad kfs header #1\n");
        return -1;
      }
      binlog_headers++;
      if (kfs_Hdr[1].header_seq_num == kfs_Hdr[0].header_seq_num) {
        assert (!memcmp (kfs_Hdr + 1, kfs_Hdr, 4096));
      }
    }
  }
  r -= binlog_headers * 4096;
  if (r < 4) {
    fprintf (stderr, "no first entry in binlog\n");
    return -1;
  }
  E = (struct lev_start *) (kfs_Hdr + binlog_headers);

  switch (E->type) {
  case LEV_START:
    assert (r >= sizeof (struct lev_start));
    ST = E;
    break;
  case LEV_ROTATE_FROM:
    assert (r >= sizeof (struct lev_rotate_from));
    CONT = (struct lev_rotate_from *) E;
    break;
  default:
    fprintf (stderr, "fatal: binlog file begins with wrong entry type %08x\n", E->type);
    return -1;
  }

  binlog_existed = 1;

  if (!binlog_headers) {
    return 0;
  }

  KHDR = kfs_Hdr;
  if (binlog_headers > 1 && kfs_Hdr[1].header_seq_num > kfs_Hdr[0].header_seq_num) {
    KHDR++;
  }

  assert (KHDR->data_size + binlog_headers * 4096 == KHDR->raw_size);
  assert (lseek (fd, 0, SEEK_END) == KHDR->raw_size);

  tot_crc32 = ~KHDR->data_crc32;

  if (KHDR->finished == -1) {
    fprintf (stderr, "fatal: incomplete kfs file\n");
    return -1;
  }

  if (ST) {
    if (ST->schema_id != KHDR->schema_id) {
      fprintf (stderr, "fatal: binlog schema id mismatch.\n");
      return -1;
    }
    if (ST->split_min != KHDR->split_min || ST->split_max != KHDR->split_max || ST->split_mod != KHDR->split_mod) {
      fprintf (stderr, "fatal: binlog slice parameters mismatch.\n");
      return -1;
    }
    if (KHDR->log_pos) {
      fprintf (stderr, "fatal: first binlog file has non-zero log_pos %lld\n", KHDR->log_pos);
      return -1;
    }
  }

  if (CONT) {
    if (KHDR->log_pos != CONT->cur_log_pos) {
      fprintf (stderr, "fatal: continuation binlog file log_pos mismatch: %lld != %lld\n", KHDR->log_pos, CONT->cur_log_pos);
      return -1;
    }
    if (KHDR->prev_log_hash != CONT->prev_log_hash) {
      fprintf (stderr, "fatal: binlog file prev_log_hash mismatch: %016llx != %016llx\n", KHDR->prev_log_hash, CONT->prev_log_hash);
      return -1;
    }
  }

  return binlog_headers;
}