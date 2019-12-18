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
typedef  TYPE_1__* db_breakpoint_t ;
struct TYPE_4__ {struct TYPE_4__* link; } ;

/* Variables and functions */
 TYPE_1__* db_free_breakpoints ; 

__attribute__((used)) static void
db_breakpoint_free(db_breakpoint_t bkpt)
{
	bkpt->link = db_free_breakpoints;
	db_free_breakpoints = bkpt;
}