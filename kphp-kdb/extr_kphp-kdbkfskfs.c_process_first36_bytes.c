#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lev_start {int type; } ;
struct lev_rotate_from {int crc32; int timestamp; int /*<<< orphan*/  prev_log_hash; int /*<<< orphan*/  cur_log_hash; int /*<<< orphan*/  cur_log_pos; } ;
struct kfs_file_info {char* filename; TYPE_1__* khdr; int /*<<< orphan*/  log_pos; } ;
struct TYPE_2__ {int log_pos_crc32; int prev_log_time; int /*<<< orphan*/  prev_log_hash; int /*<<< orphan*/  file_id_hash; } ;

/* Variables and functions */
#define  LEV_ROTATE_FROM 129 
#define  LEV_START 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int process_first36_bytes (struct kfs_file_info *FI, int fd, int r, struct lev_start *E) {
  switch (E->type) {
    case LEV_START:
      assert (r >= sizeof (struct lev_start) - 4);
      FI->log_pos = 0;
      break;
    case LEV_ROTATE_FROM:
      assert (r >= sizeof (struct lev_rotate_from));
      FI->log_pos = ((struct lev_rotate_from *)E)->cur_log_pos;
      if (FI->khdr && FI->khdr->file_id_hash != ((struct lev_rotate_from *)E)->cur_log_hash) {
        fprintf (stderr, "warning: binlog file %s has different hash in header (%016llX) and continue record (%016llX)\n", FI->filename, FI->khdr->file_id_hash, ((struct lev_rotate_from *)E)->cur_log_hash);
        assert (close (fd) >= 0);
        return -2;
      }
      if (FI->khdr && FI->khdr->prev_log_hash != ((struct lev_rotate_from *)E)->prev_log_hash) {
        fprintf (stderr, "warning: binlog file %s has different hash of previous binlog in header (%016llX) and continue record (%016llX)\n", FI->filename, FI->khdr->prev_log_hash, ((struct lev_rotate_from *)E)->prev_log_hash);
        assert (close (fd) >= 0);
        return -2;
      }
      if (FI->khdr && FI->khdr->log_pos_crc32 != ((struct lev_rotate_from *)E)->crc32) {
        fprintf (stderr, "warning: binlog file %s has different crc32 in header (%08X) and continue record (%08X)\n", FI->filename, FI->khdr->log_pos_crc32, ((struct lev_rotate_from *)E)->crc32);
        assert (close (fd) >= 0);
        return -2;
      }
      if (FI->khdr && FI->khdr->prev_log_time != ((struct lev_rotate_from *)E)->timestamp) {
        fprintf (stderr, "warning: binlog file %s has different timestamp in header (%d) and continue record (%d)\n", FI->filename, FI->khdr->prev_log_time, ((struct lev_rotate_from *)E)->timestamp);
        assert (close (fd) >= 0);
        return -2;
      }
      break;
    default:
      fprintf (stderr, "warning: binlog file %s begins with wrong entry type %08x\n", FI->filename, E->type);
      assert (close (fd) >= 0);
      return -2;
  }
  return 0;
}