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
 void* AMDPM_SMBINW (struct amdpm_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMDPM_SMBOUTB (struct amdpm_softc*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  AMDPM_SMBOUTW (struct amdpm_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AMDPM_UNLOCK (struct amdpm_softc*) ; 
 int AMDSMB_GE_CYC_WDATA ; 
 int AMDSMB_GE_HOST_STC ; 
 int /*<<< orphan*/  AMDSMB_GLOBAL_ENABLE ; 
 int /*<<< orphan*/  AMDSMB_HSTADDR ; 
 int /*<<< orphan*/  AMDSMB_HSTCMD ; 
 int /*<<< orphan*/  AMDSMB_HSTDATA ; 
 int LSB ; 
 int SMB_EBUSY ; 
 int SMB_ENOERR ; 
 int /*<<< orphan*/  amdpm_clear (struct amdpm_softc*) ; 
 int /*<<< orphan*/  amdpm_idle (struct amdpm_softc*) ; 
 int amdpm_wait (struct amdpm_softc*) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,char,short,int) ; 

__attribute__((used)) static int
amdpm_readw(device_t dev, u_char slave, char cmd, short *word)
{
	struct amdpm_softc *sc = (struct amdpm_softc *)device_get_softc(dev);
	int error;
	u_short l;

	AMDPM_LOCK(sc);
	amdpm_clear(sc);
	if (!amdpm_idle(sc)) {
		AMDPM_UNLOCK(sc);
		return (SMB_EBUSY);
	}

	AMDPM_SMBOUTW(sc, AMDSMB_HSTADDR, slave | LSB);
	AMDPM_SMBOUTB(sc, AMDSMB_HSTCMD, cmd);
	l = AMDPM_SMBINW(sc, AMDSMB_GLOBAL_ENABLE);
	AMDPM_SMBOUTW(sc, AMDSMB_GLOBAL_ENABLE, (l & 0xfff8) | AMDSMB_GE_CYC_WDATA | AMDSMB_GE_HOST_STC);

	if ((error = amdpm_wait(sc)) == SMB_ENOERR)
		*word = AMDPM_SMBINW(sc, AMDSMB_HSTDATA);

	AMDPM_DEBUG(printf("amdpm: READW from 0x%x, cmd=0x%x, word=0x%x, error=0x%x\n", slave, cmd, *word, error));
	AMDPM_UNLOCK(sc);

	return (error);
}