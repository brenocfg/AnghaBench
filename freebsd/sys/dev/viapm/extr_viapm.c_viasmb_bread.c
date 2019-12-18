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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int LSB ; 
 int /*<<< orphan*/  SMBHADDR ; 
 int /*<<< orphan*/  SMBHBLOCK ; 
 int /*<<< orphan*/  SMBHCMD ; 
 int /*<<< orphan*/  SMBHCTRL ; 
 char SMBHCTRL_BLOCK ; 
 char SMBHCTRL_START ; 
 int /*<<< orphan*/  SMBHDATA0 ; 
 int SMB_EBUSY ; 
 int SMB_EINVAL ; 
 int SMB_ENOERR ; 
 int /*<<< orphan*/  VIAPM_DEBUG (int /*<<< orphan*/ ) ; 
 int VIAPM_INB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIAPM_LOCK (struct viapm_softc*) ; 
 int /*<<< orphan*/  VIAPM_OUTB (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  VIAPM_UNLOCK (struct viapm_softc*) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,char,int) ; 
 scalar_t__ viapm_busy (struct viapm_softc*) ; 
 int /*<<< orphan*/  viapm_clear (struct viapm_softc*) ; 
 int viapm_wait (struct viapm_softc*) ; 

__attribute__((used)) static int
viasmb_bread(device_t dev, u_char slave, char cmd, u_char *count, char *buf)
{
	struct viapm_softc *viapm = (struct viapm_softc *)device_get_softc(dev);
	u_char data, len, i;
	int error;

	if (*count < 1 || *count > 32)
		return (SMB_EINVAL);

	VIAPM_LOCK(viapm);
	viapm_clear(viapm);
	if (viapm_busy(viapm)) {
		VIAPM_UNLOCK(viapm);
		return (SMB_EBUSY);
	}

	VIAPM_OUTB(SMBHADDR, slave | LSB);
	VIAPM_OUTB(SMBHCMD, cmd);
	VIAPM_OUTB(SMBHCTRL, SMBHCTRL_START | SMBHCTRL_BLOCK);

	if ((error = viapm_wait(viapm)) != SMB_ENOERR)
		goto error;

	len = VIAPM_INB(SMBHDATA0);
	i = VIAPM_INB(SMBHCTRL); 		/* reset counter */

	/* read the 32-byte internal buffer */
	for (i = 0; i < len; i++) {
		data = VIAPM_INB(SMBHBLOCK);
		if (i < *count)
			buf[i] = data;
		DELAY(2);
	}
	*count = len;

error:
	VIAPM_DEBUG(printf("viapm: READBLK to 0x%x, count=0x%x, cmd=0x%x, error=0x%x", slave, *count, cmd, error));
	VIAPM_UNLOCK(viapm);

	return (error);
}