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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct jzsmb_softc {int busy; int /*<<< orphan*/ * msg; scalar_t__ status; int /*<<< orphan*/  mtx; } ;
struct iic_msg {scalar_t__ slave; int flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IIC_M_RD ; 
 int /*<<< orphan*/  SMBCON ; 
 int /*<<< orphan*/  SMBCON_STPHLD ; 
 int /*<<< orphan*/  SMB_LOCK (struct jzsmb_softc*) ; 
 int /*<<< orphan*/  SMB_READ (struct jzsmb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMB_UNLOCK (struct jzsmb_softc*) ; 
 int /*<<< orphan*/  SMB_WRITE (struct jzsmb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct jzsmb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jzsmb_enable (struct jzsmb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jzsmb_reset_locked (int /*<<< orphan*/ ,scalar_t__) ; 
 int jzsmb_transfer_read (int /*<<< orphan*/ ,struct iic_msg*) ; 
 int jzsmb_transfer_write (int /*<<< orphan*/ ,struct iic_msg*,int) ; 
 int /*<<< orphan*/  mtx_sleep (struct jzsmb_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct jzsmb_softc*) ; 

__attribute__((used)) static int
jzsmb_transfer(device_t dev, struct iic_msg *msgs, uint32_t nmsgs)
{
	struct jzsmb_softc *sc;
	uint32_t n;
	uint16_t con;
	int error;

	sc = device_get_softc(dev);

	SMB_LOCK(sc);
	while (sc->busy)
		mtx_sleep(sc, &sc->mtx, 0, "i2cbuswait", 0);
	sc->busy = 1;
	sc->status = 0;

	for (n = 0; n < nmsgs; n++) {
		/* Set target address */
		if (n == 0 || msgs[n].slave != msgs[n - 1].slave)
			jzsmb_reset_locked(dev, msgs[n].slave);

		/* Set read or write */
		if ((msgs[n].flags & IIC_M_RD) != 0)
			error = jzsmb_transfer_read(dev, &msgs[n]);
		else
			error = jzsmb_transfer_write(dev, &msgs[n],
			    n < nmsgs - 1);

		if (error != 0)
			goto done;
	}

done:
	/* Send stop if necessary */
	con = SMB_READ(sc, SMBCON);
	con &= ~SMBCON_STPHLD;
	SMB_WRITE(sc, SMBCON, con);

	/* Disable SMB */
	jzsmb_enable(sc, 0);

	sc->msg = NULL;
	sc->busy = 0;
	wakeup(sc);
	SMB_UNLOCK(sc);

	return (error);
}