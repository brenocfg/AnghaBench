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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;
typedef  int /*<<< orphan*/  XS_T ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_DMAFREE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_LOGWARN ; 
 int /*<<< orphan*/  SCSI_GOOD ; 
 int /*<<< orphan*/  XS_SET_RESID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XS_STSP (int /*<<< orphan*/ *) ; 
 scalar_t__ XS_XFRLEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isp_destroy_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * isp_find_xs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_prt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isp_fastpost_complete(ispsoftc_t *isp, uint32_t fph)
{
	XS_T *xs;

	if (fph == 0) {
		return;
	}
	xs = isp_find_xs(isp, fph);
	if (xs == NULL) {
		isp_prt(isp, ISP_LOGWARN,
		    "Command for fast post handle 0x%x not found", fph);
		return;
	}
	isp_destroy_handle(isp, fph);

	/*
	 * Since we don't have a result queue entry item,
	 * we must believe that SCSI status is zero and
	 * that all data transferred.
	 */
	XS_SET_RESID(xs, 0);
	*XS_STSP(xs) = SCSI_GOOD;
	if (XS_XFRLEN(xs)) {
		ISP_DMAFREE(isp, xs, fph);
	}
	isp_done(xs);
}