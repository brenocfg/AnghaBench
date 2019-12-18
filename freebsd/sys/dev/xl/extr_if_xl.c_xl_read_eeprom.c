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
typedef  int /*<<< orphan*/  u_int16_t ;
struct xl_softc {int xl_flags; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_2 (struct xl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct xl_softc*,int /*<<< orphan*/ ,int) ; 
 int EEPROM_5BIT_OFFSET (int) ; 
 int EEPROM_8BIT_OFFSET (int) ; 
 int XL_EE_8BIT_READ ; 
 int XL_EE_READ ; 
 int XL_FLAG_8BITROM ; 
 int XL_FLAG_EEPROM_OFFSET_30 ; 
 int /*<<< orphan*/  XL_SEL_WIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XL_W0_EE_CMD ; 
 int /*<<< orphan*/  XL_W0_EE_DATA ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int xl_eeprom_wait (struct xl_softc*) ; 

__attribute__((used)) static int
xl_read_eeprom(struct xl_softc *sc, caddr_t dest, int off, int cnt, int swap)
{
	int			err = 0, i;
	u_int16_t		word = 0, *ptr;

#define EEPROM_5BIT_OFFSET(A) ((((A) << 2) & 0x7F00) | ((A) & 0x003F))
#define EEPROM_8BIT_OFFSET(A) ((A) & 0x003F)
	/*
	 * XXX: WARNING! DANGER!
	 * It's easy to accidentally overwrite the rom content!
	 * Note: the 3c575 uses 8bit EEPROM offsets.
	 */
	XL_SEL_WIN(0);

	if (xl_eeprom_wait(sc))
		return (1);

	if (sc->xl_flags & XL_FLAG_EEPROM_OFFSET_30)
		off += 0x30;

	for (i = 0; i < cnt; i++) {
		if (sc->xl_flags & XL_FLAG_8BITROM)
			CSR_WRITE_2(sc, XL_W0_EE_CMD,
			    XL_EE_8BIT_READ | EEPROM_8BIT_OFFSET(off + i));
		else
			CSR_WRITE_2(sc, XL_W0_EE_CMD,
			    XL_EE_READ | EEPROM_5BIT_OFFSET(off + i));
		err = xl_eeprom_wait(sc);
		if (err)
			break;
		word = CSR_READ_2(sc, XL_W0_EE_DATA);
		ptr = (u_int16_t *)(dest + (i * 2));
		if (swap)
			*ptr = ntohs(word);
		else
			*ptr = word;
	}

	return (err ? 1 : 0);
}