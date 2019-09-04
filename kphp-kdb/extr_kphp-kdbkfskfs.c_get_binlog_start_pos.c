#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kfs_file_info {scalar_t__ kfs_file_type; long long log_pos; scalar_t__ file_size; } ;
typedef  TYPE_1__* kfs_replica_handle_t ;
struct TYPE_3__ {int binlog_num; struct kfs_file_info** binlogs; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ close (int) ; 
 scalar_t__ kfs_binlog ; 
 long long kfs_get_binlog_file_size (struct kfs_file_info*) ; 
 int preload_file_info (struct kfs_file_info*) ; 

long long get_binlog_start_pos (kfs_replica_handle_t R, int binlog_id, long long *end_pos) {
  if (!R || binlog_id < 0 || binlog_id >= R->binlog_num) {
    return -1;
  }
  int fd = preload_file_info (R->binlogs[binlog_id]);
  if (fd == -2) {
    return -1;
  }
  if (fd >= 0) {
    assert (close (fd) >= 0);
  }
  struct kfs_file_info *FI = R->binlogs[binlog_id];
  assert (FI->kfs_file_type == kfs_binlog && FI->log_pos >= 0 && FI->file_size >= 0);
  if (end_pos) {
    *end_pos = FI->log_pos + kfs_get_binlog_file_size (FI);
  }
  return FI->log_pos;
}