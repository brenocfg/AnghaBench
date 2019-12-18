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
typedef  int u_int8_t ;
typedef  int /*<<< orphan*/  csa_res ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_CLKCR1 ; 
 int /*<<< orphan*/  BA0_SERBAD ; 
 int /*<<< orphan*/  BA0_SERBCM ; 
 int /*<<< orphan*/  BA0_SERBST ; 
 int /*<<< orphan*/  BA0_SERBWP ; 
 int CLKCR1_SWCE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int SERBCM_WRC ; 
 int SERBST_WBSY ; 
 int csa_readio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csa_writeio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
csa_clearserialfifos(csa_res *resp)
{
	int i, j, pwr;
	u_int8_t clkcr1, serbst;

	/*
	 * See if the devices are powered down.  If so, we must power them up first
	 * or they will not respond.
	 */
	pwr = 1;
	clkcr1 = csa_readio(resp, BA0_CLKCR1);
	if ((clkcr1 & CLKCR1_SWCE) == 0) {
		csa_writeio(resp, BA0_CLKCR1, clkcr1 | CLKCR1_SWCE);
		pwr = 0;
	}

	/*
	 * We want to clear out the serial port FIFOs so we don't end up playing
	 * whatever random garbage happens to be in them.  We fill the sample FIFOs
	 * with zero (silence).
	 */
	csa_writeio(resp, BA0_SERBWP, 0);

	/* Fill all 256 sample FIFO locations. */
	serbst = 0;
	for (i = 0 ; i < 256 ; i++) {
		/* Make sure the previous FIFO write operation has completed. */
		for (j = 0 ; j < 5 ; j++) {
			DELAY(100);
			serbst = csa_readio(resp, BA0_SERBST);
			if ((serbst & SERBST_WBSY) == 0)
				break;
		}
		if ((serbst & SERBST_WBSY) != 0) {
			if (!pwr)
				csa_writeio(resp, BA0_CLKCR1, clkcr1);
		}
		/* Write the serial port FIFO index. */
		csa_writeio(resp, BA0_SERBAD, i);
		/* Tell the serial port to load the new value into the FIFO location. */
		csa_writeio(resp, BA0_SERBCM, SERBCM_WRC);
	}
	/*
	 *  Now, if we powered up the devices, then power them back down again.
	 *  This is kinda ugly, but should never happen.
	 */
	if (!pwr)
		csa_writeio(resp, BA0_CLKCR1, clkcr1);
}