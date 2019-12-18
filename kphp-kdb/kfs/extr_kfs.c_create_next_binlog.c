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
typedef  int /*<<< orphan*/  kfs_hash_t ;
typedef  int /*<<< orphan*/  kfs_file_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  create_next_binlog_ext (int /*<<< orphan*/ ,long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kfs_file_handle_t create_next_binlog (kfs_file_handle_t F, long long start_log_pos, kfs_hash_t new_file_hash) {
  return create_next_binlog_ext (F, start_log_pos, new_file_hash, 0, 0);
}