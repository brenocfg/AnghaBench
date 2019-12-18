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
struct TYPE_2__ {int /*<<< orphan*/  drain_sch; int /*<<< orphan*/  schedhash; } ;

/* Variables and functions */
 TYPE_1__ dn_cfg ; 
 int /*<<< orphan*/  dn_ht_scan_bucket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drain_scheduler_sch_cb ; 

void
dn_drain_scheduler(void)
{
	dn_ht_scan_bucket(dn_cfg.schedhash, &dn_cfg.drain_sch,
			   drain_scheduler_sch_cb, NULL);
	dn_cfg.drain_sch++;
}