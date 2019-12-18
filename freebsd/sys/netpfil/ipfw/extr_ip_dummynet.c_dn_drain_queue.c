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
struct TYPE_2__ {int /*<<< orphan*/  drain_fs; int /*<<< orphan*/  fshash; } ;

/* Variables and functions */
 TYPE_1__ dn_cfg ; 
 int /*<<< orphan*/  dn_ht_scan_bucket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drain_queue_fs_cb ; 

void
dn_drain_queue(void)
{
	/* scan a bucket of flowset */
	dn_ht_scan_bucket(dn_cfg.fshash, &dn_cfg.drain_fs,
                               drain_queue_fs_cb, NULL);
	dn_cfg.drain_fs++;
}