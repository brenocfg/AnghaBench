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
struct isp_fc {int simqfrozen; int /*<<< orphan*/ * sim; } ;
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 struct isp_fc* ISP_FC_PC (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ISP_LOGDEBUG0 ; 
 int SIMQFRZ_LOOPDOWN ; 
 int /*<<< orphan*/  isp_prt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xpt_release_boot () ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
isp_unfreeze_loopdown(ispsoftc_t *isp, int chan)
{
	struct isp_fc *fc = ISP_FC_PC(isp, chan);

	if (fc->sim == NULL)
		return;
	int wasfrozen = fc->simqfrozen & SIMQFRZ_LOOPDOWN;
	fc->simqfrozen &= ~SIMQFRZ_LOOPDOWN;
	if (wasfrozen && fc->simqfrozen == 0) {
		isp_prt(isp, ISP_LOGDEBUG0,
		    "Chan %d Release simq", chan);
		xpt_release_simq(fc->sim, 1);
		xpt_release_boot();
	}
}