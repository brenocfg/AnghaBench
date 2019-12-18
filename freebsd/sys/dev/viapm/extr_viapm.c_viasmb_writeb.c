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
 int LSB ; 
 int /*<<< orphan*/  SMBHADDR ; 
 int /*<<< orphan*/  SMBHCMD ; 
 int /*<<< orphan*/  SMBHCTRL ; 
 char SMBHCTRL_BYTE ; 
 char SMBHCTRL_START ; 
 int /*<<< orphan*/  SMBHDATA0 ; 
 int SMB_EBUSY ; 
 int /*<<< orphan*/  VIAPM_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIAPM_LOCK (struct viapm_softc*) ; 
 int /*<<< orphan*/  VIAPM_OUTB (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  VIAPM_UNLOCK (struct viapm_softc*) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,char,char,int) ; 
 scalar_t__ viapm_busy (struct viapm_softc*) ; 
 int /*<<< orphan*/  viapm_clear (struct viapm_softc*) ; 
 int viapm_wait (struct viapm_softc*) ; 

__attribute__((used)) static int
viasmb_writeb(device_t dev, u_char slave, char cmd, char byte)
{
	struct viapm_softc *viapm = (struct viapm_softc *)device_get_softc(dev);
	int error;

	VIAPM_LOCK(viapm);
	viapm_clear(viapm);
	if (viapm_busy(viapm)) {
		VIAPM_UNLOCK(viapm);
		return (SMB_EBUSY);
	}

	VIAPM_OUTB(SMBHADDR, slave & ~ LSB);
	VIAPM_OUTB(SMBHCMD, cmd);
	VIAPM_OUTB(SMBHDATA0, byte);

	VIAPM_OUTB(SMBHCTRL, SMBHCTRL_START | SMBHCTRL_BYTE);

	error = viapm_wait(viapm);

	VIAPM_DEBUG(printf("viapm: WRITEB to 0x%x, cmd=0x%x, byte=0x%x, error=0x%x\n", slave, cmd, byte, error));
	VIAPM_UNLOCK(viapm);

	return (error);
}