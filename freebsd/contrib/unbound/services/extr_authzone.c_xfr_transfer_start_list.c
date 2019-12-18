#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct auth_xfer {TYPE_1__* task_transfer; } ;
struct auth_master {int /*<<< orphan*/  host; } ;
struct TYPE_6__ {int /*<<< orphan*/ * list; } ;
struct TYPE_5__ {int /*<<< orphan*/ * list; } ;
struct TYPE_4__ {TYPE_3__* scan_target; int /*<<< orphan*/ * scan_addr; TYPE_3__* masters; TYPE_2__* scan_specific; } ;

/* Variables and functions */
 TYPE_2__* find_master_by_host (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfr_transfer_start_list(struct auth_xfer* xfr, struct auth_master* spec) 
{
	if(spec) {
		xfr->task_transfer->scan_specific = find_master_by_host(
			xfr->task_transfer->masters, spec->host);
		if(xfr->task_transfer->scan_specific) {
			xfr->task_transfer->scan_target = NULL;
			xfr->task_transfer->scan_addr = NULL;
			if(xfr->task_transfer->scan_specific->list)
				xfr->task_transfer->scan_addr =
					xfr->task_transfer->scan_specific->list;
			return;
		}
	}
	/* no specific (notified) host to scan */
	xfr->task_transfer->scan_specific = NULL;
	xfr->task_transfer->scan_addr = NULL;
	/* pick up first scan target */
	xfr->task_transfer->scan_target = xfr->task_transfer->masters;
	if(xfr->task_transfer->scan_target && xfr->task_transfer->
		scan_target->list)
		xfr->task_transfer->scan_addr =
			xfr->task_transfer->scan_target->list;
}