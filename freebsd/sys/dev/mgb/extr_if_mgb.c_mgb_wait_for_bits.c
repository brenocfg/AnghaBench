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
struct mgb_softc {int dummy; } ;

/* Variables and functions */
 int CSR_READ_REG (struct mgb_softc*,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int MGB_STS_OK ; 
 int MGB_STS_TIMEOUT ; 
 int /*<<< orphan*/  MGB_TIMEOUT ; 

__attribute__((used)) static int
mgb_wait_for_bits(struct mgb_softc *sc, int reg, int set_bits, int clear_bits)
{
	int i, val;

	i = 0;
	do {
		/*
		 * XXX: Datasheets states delay should be > 5 microseconds
		 * for device reset.
		 */
		DELAY(100);
		val = CSR_READ_REG(sc, reg);
		if ((val & set_bits) == set_bits &&
		    (val & clear_bits) == 0)
			return MGB_STS_OK;
	} while (i++ < MGB_TIMEOUT);

	return MGB_STS_TIMEOUT;
}