#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ipf_state; } ;
typedef  TYPE_1__ ipf_main_softc_t ;
struct TYPE_8__ {int /*<<< orphan*/ * ftp_pendstate; int /*<<< orphan*/ * ftp_pendnat; } ;
typedef  TYPE_2__ ftpinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RWLOCK_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipf_nat_setpending (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipf_state_setpending (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
ipf_p_ftp_setpending(ipf_main_softc_t *softc, ftpinfo_t *ftp)
{
	if (ftp->ftp_pendnat != NULL)
		ipf_nat_setpending(softc, ftp->ftp_pendnat);

	if (ftp->ftp_pendstate != NULL) {
		READ_ENTER(&softc->ipf_state);
		ipf_state_setpending(softc, ftp->ftp_pendstate);
		RWLOCK_EXIT(&softc->ipf_state);
	}
}