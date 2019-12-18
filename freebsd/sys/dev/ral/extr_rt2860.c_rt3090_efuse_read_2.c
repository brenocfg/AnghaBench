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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct rt2860_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int RAL_READ (struct rt2860_softc*,int) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2860_softc*,int,int) ; 
 int RT3070_EFSROM_AIN_MASK ; 
 int RT3070_EFSROM_AIN_SHIFT ; 
 int RT3070_EFSROM_KICK ; 
 int RT3070_EFSROM_MODE_MASK ; 
 int RT3070_EFUSE_AOUT_MASK ; 
 int RT3070_EFUSE_CTRL ; 
 int RT3070_EFUSE_DATA3 ; 

__attribute__((used)) static uint16_t
rt3090_efuse_read_2(struct rt2860_softc *sc, uint16_t addr)
{
	uint32_t tmp;
	uint16_t reg;
	int ntries;

	addr *= 2;
	/*-
	 * Read one 16-byte block into registers EFUSE_DATA[0-3]:
	 * DATA0: F E D C
	 * DATA1: B A 9 8
	 * DATA2: 7 6 5 4
	 * DATA3: 3 2 1 0
	 */
	tmp = RAL_READ(sc, RT3070_EFUSE_CTRL);
	tmp &= ~(RT3070_EFSROM_MODE_MASK | RT3070_EFSROM_AIN_MASK);
	tmp |= (addr & ~0xf) << RT3070_EFSROM_AIN_SHIFT | RT3070_EFSROM_KICK;
	RAL_WRITE(sc, RT3070_EFUSE_CTRL, tmp);
	for (ntries = 0; ntries < 500; ntries++) {
		tmp = RAL_READ(sc, RT3070_EFUSE_CTRL);
		if (!(tmp & RT3070_EFSROM_KICK))
			break;
		DELAY(2);
	}
	if (ntries == 500)
		return 0xffff;

	if ((tmp & RT3070_EFUSE_AOUT_MASK) == RT3070_EFUSE_AOUT_MASK)
		return 0xffff;	/* address not found */

	/* determine to which 32-bit register our 16-bit word belongs */
	reg = RT3070_EFUSE_DATA3 - (addr & 0xc);
	tmp = RAL_READ(sc, reg);

	return (addr & 2) ? tmp >> 16 : tmp & 0xffff;
}