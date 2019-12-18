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
typedef  int u_char ;
struct amdpm_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMDPM_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMDPM_LOCK (struct amdpm_softc*) ; 
 int AMDPM_SMBINW (struct amdpm_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMDPM_SMBOUTB (struct amdpm_softc*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  AMDPM_SMBOUTW (struct amdpm_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AMDPM_UNLOCK (struct amdpm_softc*) ; 
 int AMDSMB_GE_CYC_BLOCK ; 
 int AMDSMB_GE_HOST_STC ; 
 int /*<<< orphan*/  AMDSMB_GLOBAL_ENABLE ; 
 int /*<<< orphan*/  AMDSMB_HSTADDR ; 
 int /*<<< orphan*/  AMDSMB_HSTCMD ; 
 int /*<<< orphan*/  AMDSMB_HSTDATA ; 
 int /*<<< orphan*/  AMDSMB_HSTDFIFO ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int LSB ; 
 int SMB_EBUSY ; 
 int SMB_EINVAL ; 
 int /*<<< orphan*/  amdpm_clear (struct amdpm_softc*) ; 
 int /*<<< orphan*/  amdpm_idle (struct amdpm_softc*) ; 
 int amdpm_wait (struct amdpm_softc*) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,char,int) ; 

__attribute__((used)) static int
amdpm_bwrite(device_t dev, u_char slave, char cmd, u_char count, char *buf)
{
	struct amdpm_softc *sc = (struct amdpm_softc *)device_get_softc(dev);
	u_char i;
	int error;
	u_short l;

	if (count < 1 || count > 32)
		return (SMB_EINVAL);

	AMDPM_LOCK(sc);
	amdpm_clear(sc);
	if (!amdpm_idle(sc)) {
		AMDPM_UNLOCK(sc);
		return (SMB_EBUSY);
	}

	AMDPM_SMBOUTW(sc, AMDSMB_HSTADDR, slave & ~LSB);
	
	/*
	 * Do we have to reset the internal 32-byte buffer?
	 * Can't see how to do this from the data sheet.
	 */
	AMDPM_SMBOUTW(sc, AMDSMB_HSTDATA, count);

	/* Fill the 32-byte internal buffer */
	for (i = 0; i < count; i++) {
		AMDPM_SMBOUTB(sc, AMDSMB_HSTDFIFO, buf[i]);
		DELAY(2);
	}
	AMDPM_SMBOUTB(sc, AMDSMB_HSTCMD, cmd);
	l = AMDPM_SMBINW(sc, AMDSMB_GLOBAL_ENABLE);
	AMDPM_SMBOUTW(sc, AMDSMB_GLOBAL_ENABLE,
	    (l & 0xfff8) | AMDSMB_GE_CYC_BLOCK | AMDSMB_GE_HOST_STC);

	error = amdpm_wait(sc);

	AMDPM_DEBUG(printf("amdpm: WRITEBLK to 0x%x, count=0x%x, cmd=0x%x, error=0x%x", slave, count, cmd, error));
	AMDPM_UNLOCK(sc);

	return (error);
}