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
typedef  int uint16_t ;
struct dc_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ CSR_READ_4 (struct dc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct dc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC_ROM ; 
 int /*<<< orphan*/  DC_SIO ; 
 int DC_SIO_ROMCTL_READ ; 
 int DC_SIO_ROMSEL ; 
 int /*<<< orphan*/  SIO_CLR (int) ; 
 int /*<<< orphan*/  SIO_SET (int) ; 

__attribute__((used)) static void
dc_eeprom_getword_xircom(struct dc_softc *sc, int addr, uint16_t *dest)
{

	SIO_SET(DC_SIO_ROMSEL | DC_SIO_ROMCTL_READ);

	addr *= 2;
	CSR_WRITE_4(sc, DC_ROM, addr | 0x160);
	*dest = (uint16_t)CSR_READ_4(sc, DC_SIO) & 0xff;
	addr += 1;
	CSR_WRITE_4(sc, DC_ROM, addr | 0x160);
	*dest |= ((uint16_t)CSR_READ_4(sc, DC_SIO) & 0xff) << 8;

	SIO_CLR(DC_SIO_ROMSEL | DC_SIO_ROMCTL_READ);
}