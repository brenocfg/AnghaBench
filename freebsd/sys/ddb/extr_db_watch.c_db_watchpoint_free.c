#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* db_watchpoint_t ;
struct TYPE_4__ {struct TYPE_4__* link; } ;

/* Variables and functions */
 TYPE_1__* db_free_watchpoints ; 

__attribute__((used)) static void
db_watchpoint_free(db_watchpoint_t watch)
{
	watch->link = db_free_watchpoints;
	db_free_watchpoints = watch;
}