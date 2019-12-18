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
typedef  int u_char ;
struct viapm_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  SMBHST ; 
 int SMBHST_BUSY ; 
 int SMBHST_COLLID ; 
 int SMBHST_ERROR ; 
 int SMBHST_FAILED ; 
 int SMBHST_INTR ; 
 int SMB_EABORT ; 
 int SMB_EBUSERR ; 
 int SMB_ENOACK ; 
 int SMB_ENOERR ; 
 int SMB_ETIMEOUT ; 
 int /*<<< orphan*/  VIAPM_DEBUG (int /*<<< orphan*/ ) ; 
 int VIAPM_INB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIAPM_LOCK_ASSERT (struct viapm_softc*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  viapm_abort (struct viapm_softc*) ; 
 int /*<<< orphan*/  viapm_clear (struct viapm_softc*) ; 

__attribute__((used)) static int
viapm_wait(struct viapm_softc *viapm)
{
	int count = 10000;
	u_char sts = 0;
	int error;

	VIAPM_LOCK_ASSERT(viapm);

	/* wait for command to complete and SMBus controller is idle */
	while(count--) {
		DELAY(10);
		sts = VIAPM_INB(SMBHST);

		/* check if the controller is processing a command */
		if (!(sts & SMBHST_BUSY) && (sts & SMBHST_INTR))
			break;
	}

	VIAPM_DEBUG(printf("viapm: SMBHST=0x%x\n", sts));

	error = SMB_ENOERR;

	if (!count)
		error |= SMB_ETIMEOUT;

	if (sts & SMBHST_FAILED)
		error |= SMB_EABORT;

	if (sts & SMBHST_COLLID)
		error |= SMB_ENOACK;

	if (sts & SMBHST_ERROR)
		error |= SMB_EBUSERR;

	if (error != SMB_ENOERR)
		viapm_abort(viapm);

	viapm_clear(viapm);

	return (error);
}