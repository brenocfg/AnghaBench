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
typedef  scalar_t__ u_int32_t ;
struct safe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ READ_REG (struct safe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAFE_RNG_ALM_CNT ; 
 int /*<<< orphan*/  SAFE_RNG_CNFG ; 
 int /*<<< orphan*/  SAFE_RNG_CTRL ; 
 int SAFE_RNG_MAXWAIT ; 
 int /*<<< orphan*/  SAFE_RNG_OUT ; 
 int /*<<< orphan*/  WRITE_REG (struct safe_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
safe_rng_init(struct safe_softc *sc)
{
	u_int32_t w, v;
	int i;

	WRITE_REG(sc, SAFE_RNG_CTRL, 0);
	/* use default value according to the manual */
	WRITE_REG(sc, SAFE_RNG_CNFG, 0x834);	/* magic from SafeNet */
	WRITE_REG(sc, SAFE_RNG_ALM_CNT, 0);

	/*
	 * There is a bug in rev 1.0 of the 1140 that when the RNG
	 * is brought out of reset the ready status flag does not
	 * work until the RNG has finished its internal initialization.
	 *
	 * So in order to determine the device is through its
	 * initialization we must read the data register, using the
	 * status reg in the read in case it is initialized.  Then read
	 * the data register until it changes from the first read.
	 * Once it changes read the data register until it changes
	 * again.  At this time the RNG is considered initialized. 
	 * This could take between 750ms - 1000ms in time.
	 */
	i = 0;
	w = READ_REG(sc, SAFE_RNG_OUT);
	do {
		v = READ_REG(sc, SAFE_RNG_OUT);
		if (v != w) {
			w = v;
			break;
		}
		DELAY(10);
	} while (++i < SAFE_RNG_MAXWAIT);

	/* Wait Until data changes again */
	i = 0;
	do {
		v = READ_REG(sc, SAFE_RNG_OUT);
		if (v != w)
			break;
		DELAY(10);
	} while (++i < SAFE_RNG_MAXWAIT);
}