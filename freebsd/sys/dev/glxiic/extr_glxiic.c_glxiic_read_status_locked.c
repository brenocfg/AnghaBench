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
typedef  int /*<<< orphan*/  uint8_t ;
struct glxiic_softc {int /*<<< orphan*/  smb_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLXIIC_ASSERT_LOCKED (struct glxiic_softc*) ; 
 int /*<<< orphan*/  GLXIIC_SMB_STS ; 
 int GLXIIC_SMB_STS_BER_BIT ; 
 int GLXIIC_SMB_STS_NEGACK_BIT ; 
 int GLXIIC_SMB_STS_NMATCH_BIT ; 
 int GLXIIC_SMB_STS_SLVSTP_BIT ; 
 int /*<<< orphan*/  bus_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint8_t
glxiic_read_status_locked(struct glxiic_softc *sc)
{
	uint8_t status;

	GLXIIC_ASSERT_LOCKED(sc);

	status = bus_read_1(sc->smb_res, GLXIIC_SMB_STS);

	/* Clear all status flags except SDAST and STASTR after reading. */
	bus_write_1(sc->smb_res, GLXIIC_SMB_STS, (GLXIIC_SMB_STS_SLVSTP_BIT |
		GLXIIC_SMB_STS_BER_BIT | GLXIIC_SMB_STS_NEGACK_BIT |
		GLXIIC_SMB_STS_NMATCH_BIT));

	return (status);
}