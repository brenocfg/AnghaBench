#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* x; } ;
typedef  TYPE_2__ tree_binlog_wait_t ;
struct TYPE_4__ {int wait_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  binlog_wait_time_tree ; 
 int next_binlog_wait_time ; 
 TYPE_2__* tree_get_min_binlog_wait (int /*<<< orphan*/ ) ; 

void tl_update_next_binlog_wait_time (void) {
  tree_binlog_wait_t *T = tree_get_min_binlog_wait (binlog_wait_time_tree);
  next_binlog_wait_time = T ? T->x->wait_pos : 0x7fffffffffffffffll;
}