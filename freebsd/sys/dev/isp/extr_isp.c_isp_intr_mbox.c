#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {int isp_obits; int /*<<< orphan*/ * isp_mboxtmp; int /*<<< orphan*/  isp_mboxbsy; } ;
typedef  TYPE_1__ ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_LOGWARN ; 
 int ISP_NMBOX (TYPE_1__*) ; 
 int /*<<< orphan*/  ISP_READ (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBOX_NOTIFY_COMPLETE (TYPE_1__*) ; 
 int /*<<< orphan*/  MBOX_OFF (int) ; 
 int /*<<< orphan*/  isp_prt (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
isp_intr_mbox(ispsoftc_t *isp, uint16_t mbox0)
{
	int i, obits;

	if (!isp->isp_mboxbsy) {
		isp_prt(isp, ISP_LOGWARN, "mailbox 0x%x with no waiters", mbox0);
		return;
	}
	obits = isp->isp_obits;
	isp->isp_mboxtmp[0] = mbox0;
	for (i = 1; i < ISP_NMBOX(isp); i++) {
		if ((obits & (1 << i)) == 0)
			continue;
		isp->isp_mboxtmp[i] = ISP_READ(isp, MBOX_OFF(i));
	}
	MBOX_NOTIFY_COMPLETE(isp);
}