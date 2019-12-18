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
typedef  char u_char ;
struct intsmb_softc {int /*<<< orphan*/  io_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTSMB_LOCK (struct intsmb_softc*) ; 
 int /*<<< orphan*/  INTSMB_UNLOCK (struct intsmb_softc*) ; 
 char LSB ; 
 int /*<<< orphan*/  PIIX4_SMBHSTADD ; 
 int /*<<< orphan*/  PIIX4_SMBHSTCMD ; 
 int /*<<< orphan*/  PIIX4_SMBHSTCNT_PROT_BDATA ; 
 int /*<<< orphan*/  PIIX4_SMBHSTDAT0 ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 
 struct intsmb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int intsmb_free (struct intsmb_softc*) ; 
 int /*<<< orphan*/  intsmb_start (struct intsmb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int intsmb_stop (struct intsmb_softc*) ; 

__attribute__((used)) static int
intsmb_writeb(device_t dev, u_char slave, char cmd, char byte)
{
	struct intsmb_softc *sc = device_get_softc(dev);
	int error;

	INTSMB_LOCK(sc);
	error = intsmb_free(sc);
	if (error) {
		INTSMB_UNLOCK(sc);
		return (error);
	}
	bus_write_1(sc->io_res, PIIX4_SMBHSTADD, slave & ~LSB);
	bus_write_1(sc->io_res, PIIX4_SMBHSTCMD, cmd);
	bus_write_1(sc->io_res, PIIX4_SMBHSTDAT0, byte);
	intsmb_start(sc, PIIX4_SMBHSTCNT_PROT_BDATA, 0);
	error = intsmb_stop(sc);
	INTSMB_UNLOCK(sc);
	return (error);
}