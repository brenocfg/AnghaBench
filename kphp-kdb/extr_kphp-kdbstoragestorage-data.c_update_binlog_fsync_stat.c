#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t dir_id; int /*<<< orphan*/  st_fsync; } ;
typedef  TYPE_1__ storage_binlog_file_t ;
struct TYPE_5__ {int /*<<< orphan*/  st_fsync; } ;

/* Variables and functions */
 TYPE_3__* Dirs ; 
 int /*<<< orphan*/  update_read_stat (int /*<<< orphan*/ *,int) ; 

void update_binlog_fsync_stat (storage_binlog_file_t *B, int success) {
  update_read_stat (&Dirs[B->dir_id].st_fsync, success);
  update_read_stat (&B->st_fsync, success);
}