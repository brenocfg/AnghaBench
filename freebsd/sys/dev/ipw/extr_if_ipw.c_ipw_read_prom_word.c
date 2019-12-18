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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct ipw_softc {int dummy; } ;

/* Variables and functions */
 int IPW_EEPROM_C ; 
 int /*<<< orphan*/  IPW_EEPROM_CTL (struct ipw_softc*,int) ; 
 int IPW_EEPROM_D ; 
 int IPW_EEPROM_Q ; 
 int IPW_EEPROM_S ; 
 int IPW_EEPROM_SHIFT_D ; 
 int IPW_EEPROM_SHIFT_Q ; 
 int /*<<< orphan*/  IPW_MEM_EEPROM_CTL ; 
 int MEM_READ_4 (struct ipw_softc*,int /*<<< orphan*/ ) ; 
 int le16toh (int) ; 

__attribute__((used)) static uint16_t
ipw_read_prom_word(struct ipw_softc *sc, uint8_t addr)
{
	uint32_t tmp;
	uint16_t val;
	int n;

	/* clock C once before the first command */
	IPW_EEPROM_CTL(sc, 0);
	IPW_EEPROM_CTL(sc, IPW_EEPROM_S);
	IPW_EEPROM_CTL(sc, IPW_EEPROM_S | IPW_EEPROM_C);
	IPW_EEPROM_CTL(sc, IPW_EEPROM_S);

	/* write start bit (1) */
	IPW_EEPROM_CTL(sc, IPW_EEPROM_S | IPW_EEPROM_D);
	IPW_EEPROM_CTL(sc, IPW_EEPROM_S | IPW_EEPROM_D | IPW_EEPROM_C);

	/* write READ opcode (10) */
	IPW_EEPROM_CTL(sc, IPW_EEPROM_S | IPW_EEPROM_D);
	IPW_EEPROM_CTL(sc, IPW_EEPROM_S | IPW_EEPROM_D | IPW_EEPROM_C);
	IPW_EEPROM_CTL(sc, IPW_EEPROM_S);
	IPW_EEPROM_CTL(sc, IPW_EEPROM_S | IPW_EEPROM_C);

	/* write address A7-A0 */
	for (n = 7; n >= 0; n--) {
		IPW_EEPROM_CTL(sc, IPW_EEPROM_S |
		    (((addr >> n) & 1) << IPW_EEPROM_SHIFT_D));
		IPW_EEPROM_CTL(sc, IPW_EEPROM_S |
		    (((addr >> n) & 1) << IPW_EEPROM_SHIFT_D) | IPW_EEPROM_C);
	}

	IPW_EEPROM_CTL(sc, IPW_EEPROM_S);

	/* read data Q15-Q0 */
	val = 0;
	for (n = 15; n >= 0; n--) {
		IPW_EEPROM_CTL(sc, IPW_EEPROM_S | IPW_EEPROM_C);
		IPW_EEPROM_CTL(sc, IPW_EEPROM_S);
		tmp = MEM_READ_4(sc, IPW_MEM_EEPROM_CTL);
		val |= ((tmp & IPW_EEPROM_Q) >> IPW_EEPROM_SHIFT_Q) << n;
	}

	IPW_EEPROM_CTL(sc, 0);

	/* clear Chip Select and clock C */
	IPW_EEPROM_CTL(sc, IPW_EEPROM_S);
	IPW_EEPROM_CTL(sc, 0);
	IPW_EEPROM_CTL(sc, IPW_EEPROM_C);

	return le16toh(val);
}