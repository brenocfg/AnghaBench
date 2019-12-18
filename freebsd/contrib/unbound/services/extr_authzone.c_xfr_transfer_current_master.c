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
struct auth_xfer {TYPE_1__* task_transfer; } ;
struct auth_master {int dummy; } ;
struct TYPE_2__ {struct auth_master* scan_target; struct auth_master* scan_specific; } ;

/* Variables and functions */

__attribute__((used)) static struct auth_master*
xfr_transfer_current_master(struct auth_xfer* xfr)
{
	if(xfr->task_transfer->scan_specific)
		return xfr->task_transfer->scan_specific;
	return xfr->task_transfer->scan_target;
}