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
struct TYPE_4__ {int /*<<< orphan*/  head; int /*<<< orphan*/  lsig; } ;
typedef  TYPE_1__ leap_table_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_times (TYPE_1__*) ; 

void
leapsec_clear(
	leap_table_t * pt)
{
	memset(&pt->lsig, 0, sizeof(pt->lsig));
	memset(&pt->head, 0, sizeof(pt->head));
	reset_times(pt);
}