#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct lev_start {int type; scalar_t__ schema_id; scalar_t__ split_min; scalar_t__ split_max; scalar_t__ split_mod; } ;
struct lev_rotate_from {int cur_log_pos; int cur_log_hash; int prev_log_hash; int crc32; int timestamp; } ;
struct kfs_file_header {int dummy; } ;
struct TYPE_11__ {scalar_t__ first36_bytes; } ;
typedef  TYPE_1__ kfs_binlog_zip_header_t ;
struct TYPE_13__ {int fd; } ;
struct TYPE_12__ {scalar_t__ magic; scalar_t__ kfs_file_type; scalar_t__ header_seq_num; scalar_t__ data_size; scalar_t__ raw_size; int log_pos; int finished; scalar_t__ schema_id; scalar_t__ split_min; scalar_t__ split_max; scalar_t__ split_mod; int prev_log_hash; int file_id_hash; int log_pos_crc32; int prev_log_time; int replica_id_hash; scalar_t__ data_crc32; } ;

/* Variables and functions */
 TYPE_5__* Binlog ; 
 struct lev_rotate_from* CONT ; 
#define  KFS_BINLOG_ZIP_MAGIC 130 
 scalar_t__ KFS_MAGIC ; 
 TYPE_2__* KHDR ; 
#define  LEV_ROTATE_FROM 129 
#define  LEV_START 128 
 int /*<<< orphan*/  SEEK_SET ; 
 struct lev_start* ST ; 
 int /*<<< orphan*/  assert (int) ; 
 int binlog_existed ; 
 int binlog_headers ; 
 int /*<<< orphan*/  binlog_zipped ; 
 scalar_t__ check_kfs_header_basic (TYPE_2__*) ; 
 int cur_binlog_file_hash ; 
 int cur_replica_hash ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* kfs_Hdr ; 
 scalar_t__ kfs_binlog ; 
 int /*<<< orphan*/  kfs_buffer_crypt (TYPE_5__*,TYPE_2__*,int,long long) ; 
 int log_headers_size ; 
 int log_start_pos ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (TYPE_2__*,TYPE_2__*,int) ; 
 int read (int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ tot_crc32 ; 
 scalar_t__ tot_crc32_pos ; 

__attribute__((used)) static int load_binlog_headers (int fd) {
  int r;
  struct lev_start *E;
  assert (sizeof (struct kfs_file_header) == 4096);

  binlog_headers = 0;
  binlog_existed = 0;
  ST = 0;
  CONT = 0;
  KHDR = 0;
  cur_binlog_file_hash = 0;
  log_headers_size = 0;
  tot_crc32 = 0;
  tot_crc32_pos = 0;

  if (lseek (fd, 0, SEEK_SET) != 0) {
    fprintf (stderr, "cannot lseek binlog file %d: %m\n", fd);
    return -1;
  }

  r = read (fd, kfs_Hdr, 4096 * 3);
  if (!r) {
    return 0;
  }

  if (Binlog && Binlog->fd == fd) {
    kfs_buffer_crypt (Binlog, kfs_Hdr, r, 0LL);
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

  loop:
  switch (E->type) {
  case LEV_START:
    assert (r >= sizeof (struct lev_start) - 4);
    ST = E;
    log_start_pos = 0;
    break;
  case LEV_ROTATE_FROM:
    assert (r >= sizeof (struct lev_rotate_from));
    CONT = (struct lev_rotate_from *) E;
    log_start_pos = CONT->cur_log_pos;
    cur_binlog_file_hash = CONT->cur_log_hash;
    break;
  case KFS_BINLOG_ZIP_MAGIC:
    assert (!binlog_headers && binlog_zipped);
    assert (r >= sizeof (kfs_binlog_zip_header_t));
    /* infinite loop guard */
    assert (E == (struct lev_start *) (kfs_Hdr + binlog_headers));
    E = (struct lev_start *) ((kfs_binlog_zip_header_t *) E)->first36_bytes;
    r = 36;
    goto loop;
  default:
    fprintf (stderr, "fatal: binlog file begins with wrong entry type %08x\n", E->type);
    return -1;
  }

  binlog_existed = 1;

  if (!binlog_headers) {
    log_headers_size = 0;
    assert (lseek (fd, log_headers_size, SEEK_SET) == log_headers_size);
    return 0;
  }

  KHDR = kfs_Hdr;
  if (binlog_headers > 1 && kfs_Hdr[1].header_seq_num > kfs_Hdr[0].header_seq_num) {
    KHDR++;
  }

  assert (KHDR->data_size + binlog_headers * 4096 == KHDR->raw_size);
//  assert (lseek (fd, 0, SEEK_END) == KHDR->raw_size);

  tot_crc32 = KHDR->data_crc32;
  tot_crc32_pos = KHDR->log_pos + KHDR->data_size;

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
    if (KHDR->file_id_hash != CONT->cur_log_hash) {
      fprintf (stderr, "fatal: binlog file file_id_hash mismatch: %016llx != %016llx\n", KHDR->file_id_hash, CONT->cur_log_hash);
      return -1;
    }
    if (KHDR->log_pos_crc32 != CONT->crc32) {
      fprintf (stderr, "fatal: binlog file crc32 mismatch: %08x != %08x\n", KHDR->log_pos_crc32, CONT->crc32);
      return -1;
    }
    if (KHDR->prev_log_time != CONT->timestamp) {
      fprintf (stderr, "fatal: binlog file file_id_hash mismatch: %d != %d\n", KHDR->prev_log_time, CONT->timestamp);
      return -1;
    }
  }

  log_headers_size = binlog_headers * 4096;
  assert (lseek (fd, log_headers_size, SEEK_SET) == log_headers_size);

  if (KHDR) {
    cur_binlog_file_hash = KHDR->file_id_hash;
    if (!cur_replica_hash) {
      cur_replica_hash = KHDR->replica_id_hash;
    } else if (cur_replica_hash != KHDR->replica_id_hash) {
      fprintf (stderr, "fatal: binlog file replica_hash mismatch: %016llx != %016llx\n", KHDR->replica_id_hash, cur_replica_hash);
      return -1;
    }
  }

  return binlog_headers;
}