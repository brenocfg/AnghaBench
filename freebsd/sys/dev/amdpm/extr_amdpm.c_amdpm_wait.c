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
typedef  int u_short ;
struct amdpm_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDPM_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMDPM_LOCK_ASSERT (struct amdpm_softc*) ; 
 int AMDPM_SMBINW (struct amdpm_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMDSMB_GLOBAL_STATUS ; 
 int AMDSMB_GS_ABRT_STS ; 
 int AMDSMB_GS_COL_STS ; 
 int AMDSMB_GS_HST_STS ; 
 int AMDSMB_GS_PRERR_STS ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int SMB_EABORT ; 
 int SMB_EBUSERR ; 
 int SMB_ENOACK ; 
 int SMB_ENOERR ; 
 int SMB_ETIMEOUT ; 
 int /*<<< orphan*/  amdpm_clear (struct amdpm_softc*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static int
amdpm_wait(struct amdpm_softc *sc)
{
	int count = 10000;
	u_short sts = 0;
	int error;

	AMDPM_LOCK_ASSERT(sc);
	/* Wait for command to complete (SMBus controller is idle) */
	while(count--) {
		DELAY(10);
		sts = AMDPM_SMBINW(sc, AMDSMB_GLOBAL_STATUS);
		if (!(sts & AMDSMB_GS_HST_STS))
			break;
	}

	AMDPM_DEBUG(printf("amdpm: STS=0x%x (count=%d)\n", sts, count));

	error = SMB_ENOERR;

	if (!count)
		error |= SMB_ETIMEOUT;

	if (sts & AMDSMB_GS_ABRT_STS)
		error |= SMB_EABORT;

	if (sts & AMDSMB_GS_COL_STS)
		error |= SMB_ENOACK;

	if (sts & AMDSMB_GS_PRERR_STS)
		error |= SMB_EBUSERR;

	if (error != SMB_ENOERR)
		amdpm_clear(sc);

	return (error);
}