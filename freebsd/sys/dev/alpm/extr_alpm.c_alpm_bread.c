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
struct alpm_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALPM_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ALPM_LOCK (struct alpm_softc*) ; 
 int ALPM_SMBINB (struct alpm_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ALPM_SMBOUTB (struct alpm_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ALPM_UNLOCK (struct alpm_softc*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int LSB ; 
 int /*<<< orphan*/  SMBCMD ; 
 int /*<<< orphan*/  SMBHADDR ; 
 int /*<<< orphan*/  SMBHBLOCK ; 
 int /*<<< orphan*/  SMBHCMD ; 
 int /*<<< orphan*/  SMBHDATA ; 
 int /*<<< orphan*/  SMBSTART ; 
 int SMBWRBLOCK ; 
 int SMB_BLK_CLR ; 
 int SMB_EBUSY ; 
 int SMB_EINVAL ; 
 int SMB_ENOERR ; 
 int /*<<< orphan*/  alpm_clear (struct alpm_softc*) ; 
 int /*<<< orphan*/  alpm_idle (struct alpm_softc*) ; 
 int alpm_wait (struct alpm_softc*) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,char,int) ; 

__attribute__((used)) static int
alpm_bread(device_t dev, u_char slave, char cmd, u_char *count, char *buf)
{
	struct alpm_softc *sc = (struct alpm_softc *)device_get_softc(dev);
	u_char data, len, i;
	int error;

	if (*count < 1 || *count > 32)
		return (SMB_EINVAL);

	ALPM_LOCK(sc);
	alpm_clear(sc);
	if (!alpm_idle(sc)) {
		ALPM_UNLOCK(sc);
		return (SMB_EBUSY);
	}

	ALPM_SMBOUTB(sc, SMBHADDR, slave | LSB);
	
	/* set the cmd and reset the
	 * 32-byte long internal buffer */
	ALPM_SMBOUTB(sc, SMBCMD, SMBWRBLOCK | SMB_BLK_CLR);

	ALPM_SMBOUTB(sc, SMBHCMD, cmd);
	ALPM_SMBOUTB(sc, SMBSTART, 0xff);

	if ((error = alpm_wait(sc)) != SMB_ENOERR)
			goto error;

	len = ALPM_SMBINB(sc, SMBHDATA);

	/* read the 32-byte internal buffer */
	for (i = 0; i < len; i++) {
		data = ALPM_SMBINB(sc, SMBHBLOCK);
		if (i < *count)
			buf[i] = data;
		DELAY(2);
	}
	*count = len;

error:
	ALPM_DEBUG(printf("alpm: READBLK to 0x%x, count=0x%x, cmd=0x%x, error=0x%x", slave, *count, cmd, error));
	ALPM_UNLOCK(sc);

	return (error);
}