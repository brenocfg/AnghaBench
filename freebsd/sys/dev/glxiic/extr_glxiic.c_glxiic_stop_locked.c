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
typedef  int uint8_t ;
struct glxiic_softc {int /*<<< orphan*/  smb_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLXIIC_ASSERT_LOCKED (struct glxiic_softc*) ; 
 int /*<<< orphan*/  GLXIIC_SMB_CTRL1 ; 
 int GLXIIC_SMB_CTRL1_STOP_BIT ; 
 int /*<<< orphan*/  GLXIIC_SMB_SDA ; 
 int /*<<< orphan*/  GLXIIC_SMB_STS ; 
 int GLXIIC_SMB_STS_SDAST_BIT ; 
 int GLXIIC_SMB_STS_STASTR_BIT ; 
 int GLXIIC_SMB_STS_XMIT_BIT ; 
 int bus_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int glxiic_read_status_locked (struct glxiic_softc*) ; 

__attribute__((used)) static void
glxiic_stop_locked(struct glxiic_softc *sc)
{
	uint8_t status, ctrl1;

	GLXIIC_ASSERT_LOCKED(sc);

	status = glxiic_read_status_locked(sc);

	ctrl1 = bus_read_1(sc->smb_res, GLXIIC_SMB_CTRL1);
	bus_write_1(sc->smb_res, GLXIIC_SMB_CTRL1,
	    ctrl1 | GLXIIC_SMB_CTRL1_STOP_BIT);

	/*
	 * Perform a dummy read of SDA in master receive mode to clear
	 * SDAST if set.
	 */
	if ((status & GLXIIC_SMB_STS_XMIT_BIT) == 0 &&
	    (status & GLXIIC_SMB_STS_SDAST_BIT) != 0)
	 	bus_read_1(sc->smb_res, GLXIIC_SMB_SDA);

	/* Check stall after start bit and clear if needed */
	if ((status & GLXIIC_SMB_STS_STASTR_BIT) != 0) {
		bus_write_1(sc->smb_res, GLXIIC_SMB_STS,
		    GLXIIC_SMB_STS_STASTR_BIT);
	}
}