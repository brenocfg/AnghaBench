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
 int /*<<< orphan*/  AMDPM_SMBOUTW (struct amdpm_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AMDPM_UNLOCK (struct amdpm_softc*) ; 
 int AMDSMB_GE_CYC_BYTE ; 
 int AMDSMB_GE_HOST_STC ; 
 int /*<<< orphan*/  AMDSMB_GLOBAL_ENABLE ; 
 int /*<<< orphan*/  AMDSMB_HSTADDR ; 
 int /*<<< orphan*/  AMDSMB_HSTDATA ; 
 int LSB ; 
 int SMB_EBUSY ; 
 int /*<<< orphan*/  amdpm_clear (struct amdpm_softc*) ; 
 int /*<<< orphan*/  amdpm_idle (struct amdpm_softc*) ; 
 int amdpm_wait (struct amdpm_softc*) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,char,int) ; 

__attribute__((used)) static int
amdpm_sendb(device_t dev, u_char slave, char byte)
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

	AMDPM_SMBOUTW(sc, AMDSMB_HSTADDR, slave & ~LSB);
	AMDPM_SMBOUTW(sc, AMDSMB_HSTDATA, byte);
	l = AMDPM_SMBINW(sc, AMDSMB_GLOBAL_ENABLE);
	AMDPM_SMBOUTW(sc, AMDSMB_GLOBAL_ENABLE, (l & 0xfff8) | AMDSMB_GE_CYC_BYTE | AMDSMB_GE_HOST_STC);

	error = amdpm_wait(sc);

	AMDPM_DEBUG(printf("amdpm: SENDB to 0x%x, byte=0x%x, error=0x%x\n", slave, byte, error));
	AMDPM_UNLOCK(sc);

	return (error);
}