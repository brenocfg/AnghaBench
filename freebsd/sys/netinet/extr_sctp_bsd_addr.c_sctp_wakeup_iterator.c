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
struct TYPE_2__ {int /*<<< orphan*/  iterator_running; } ;

/* Variables and functions */
 TYPE_1__ sctp_it_ctl ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
sctp_wakeup_iterator(void)
{
	wakeup(&sctp_it_ctl.iterator_running);
}