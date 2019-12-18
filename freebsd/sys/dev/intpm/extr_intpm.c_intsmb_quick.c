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
typedef  int /*<<< orphan*/  u_char ;
struct intsmb_softc {int /*<<< orphan*/  io_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTSMB_LOCK (struct intsmb_softc*) ; 
 int /*<<< orphan*/  INTSMB_UNLOCK (struct intsmb_softc*) ; 
 int /*<<< orphan*/  LSB ; 
 int /*<<< orphan*/  PIIX4_SMBHSTADD ; 
 int /*<<< orphan*/  PIIX4_SMBHSTCNT_PROT_QUICK ; 
 int SMB_EINVAL ; 
#define  SMB_QREAD 129 
#define  SMB_QWRITE 128 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intsmb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int intsmb_free (struct intsmb_softc*) ; 
 int /*<<< orphan*/  intsmb_start (struct intsmb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int intsmb_stop (struct intsmb_softc*) ; 

__attribute__((used)) static int
intsmb_quick(device_t dev, u_char slave, int how)
{
	struct intsmb_softc *sc = device_get_softc(dev);
	int error;
	u_char data;

	data = slave;

	/* Quick command is part of Address, I think. */
	switch(how) {
	case SMB_QWRITE:
		data &= ~LSB;
		break;
	case SMB_QREAD:
		data |= LSB;
		break;
	default:
		return (SMB_EINVAL);
	}

	INTSMB_LOCK(sc);
	error = intsmb_free(sc);
	if (error) {
		INTSMB_UNLOCK(sc);
		return (error);
	}
	bus_write_1(sc->io_res, PIIX4_SMBHSTADD, data);
	intsmb_start(sc, PIIX4_SMBHSTCNT_PROT_QUICK, 0);
	error = intsmb_stop(sc);
	INTSMB_UNLOCK(sc);
	return (error);
}