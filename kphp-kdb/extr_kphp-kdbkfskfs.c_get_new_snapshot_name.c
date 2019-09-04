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
struct kfs_file_info {int dummy; } ;
typedef  TYPE_1__* kfs_replica_handle_t ;
struct TYPE_3__ {int snapshot_num; struct kfs_file_info** snapshots; } ;

/* Variables and functions */
 char* create_new_name (struct kfs_file_info*,long long,char const*,int) ; 

char *get_new_snapshot_name (kfs_replica_handle_t R, long long log_pos, const char *replica_prefix) {
  struct kfs_file_info *FI = 0;

  if (R && R->snapshot_num) {
    FI = R->snapshots[R->snapshot_num - 1];
  }

  return create_new_name (FI, log_pos, replica_prefix, 2);
}