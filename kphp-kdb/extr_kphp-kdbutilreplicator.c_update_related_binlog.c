#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct related_binlog {int /*<<< orphan*/  kfs_replica; int /*<<< orphan*/  update_generation; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int load_binlog_data (struct related_binlog*) ; 
 int /*<<< orphan*/  sigrtmax_cnt ; 
 scalar_t__ update_replica (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ) ; 

int update_related_binlog (struct related_binlog *R) {
  vkprintf (1, "reloading kfs data for %s\n", R->path);
  R->update_generation = sigrtmax_cnt;
  assert (update_replica (R->kfs_replica, 0) >= 0);
  return load_binlog_data (R);
}