#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  zcr_ereport; } ;
typedef  TYPE_1__ zio_cksum_report_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVCH_SLEEP ; 
 int /*<<< orphan*/  fm_ereport_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
zfs_ereport_send_interim_checksum(zio_cksum_report_t *report)
{
#ifdef _KERNEL
	fm_ereport_post(report->zcr_ereport, EVCH_SLEEP);
#endif
}