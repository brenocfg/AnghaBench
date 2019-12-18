#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_RUN_ISR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_UNLOCK (int /*<<< orphan*/ *) ; 

void
isp_platform_intr(void *arg)
{
	ispsoftc_t *isp = arg;

	ISP_LOCK(isp);
	ISP_RUN_ISR(isp);
	ISP_UNLOCK(isp);
}