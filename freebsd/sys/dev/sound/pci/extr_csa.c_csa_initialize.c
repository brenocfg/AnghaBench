#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  csa_res ;
struct TYPE_3__ {int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int ACCTL_ESYN ; 
 int ACCTL_RSTN ; 
 int ACCTL_VFRM ; 
 int ACISV_ISV3 ; 
 int ACISV_ISV4 ; 
 int ACOSV_SLV3 ; 
 int ACOSV_SLV4 ; 
 int ACSTS_CRDY ; 
 int /*<<< orphan*/  BA0_AC97_POWERDOWN ; 
 int /*<<< orphan*/  BA0_ACCTL ; 
 int /*<<< orphan*/  BA0_ACISV ; 
 int /*<<< orphan*/  BA0_ACOSV ; 
 int /*<<< orphan*/  BA0_ACSTS ; 
 int /*<<< orphan*/  BA0_CLKCR1 ; 
 int /*<<< orphan*/  BA0_CLKCR2 ; 
 int /*<<< orphan*/  BA0_HICR ; 
 int /*<<< orphan*/  BA0_PLLCC ; 
 int /*<<< orphan*/  BA0_PLLM ; 
 int /*<<< orphan*/  BA0_SERACC ; 
 int /*<<< orphan*/  BA0_SERBSP ; 
 int /*<<< orphan*/  BA0_SERC1 ; 
 int /*<<< orphan*/  BA0_SERC2 ; 
 int /*<<< orphan*/  BA0_SERMC1 ; 
 int CLKCR1_PLLP ; 
 int CLKCR1_SWCE ; 
 int CLKCR2_PDIVS_8 ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int HICR_CHGM ; 
 int HICR_IEV ; 
 int PLLCC_CDR_73_104_MHZ ; 
 int PLLCC_LPF_1050_2780_KHZ ; 
 int SERACC_CODEC_TYPE_1_03 ; 
 int SERACC_CODEC_TYPE_2_0 ; 
 int SERACC_HSP ; 
 int SERC1_SO1EN ; 
 int SERC1_SO1F_AC97 ; 
 int SERC2_SI1F_AC97 ; 
 int SERMC1_MSPE ; 
 int SERMC1_PTC_AC97 ; 
 int clkcr1 ; 
 int /*<<< orphan*/  csa_clearserialfifos (int /*<<< orphan*/ *) ; 
 int csa_readio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csa_writeio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
csa_initialize(sc_p scp)
{
	int i;
	u_int32_t acsts, acisv;
	csa_res *resp;

	resp = &scp->res;

	/*
	 * First, blast the clock control register to zero so that the PLL starts
	 * out in a known state, and blast the master serial port control register
	 * to zero so that the serial ports also start out in a known state.
	 */
	csa_writeio(resp, BA0_CLKCR1, 0);
	csa_writeio(resp, BA0_SERMC1, 0);

	/*
	 * If we are in AC97 mode, then we must set the part to a host controlled
	 * AC-link.  Otherwise, we won't be able to bring up the link.
	 */
#if 1
	csa_writeio(resp, BA0_SERACC, SERACC_HSP | SERACC_CODEC_TYPE_1_03); /* 1.03 codec */
#else
	csa_writeio(resp, BA0_SERACC, SERACC_HSP | SERACC_CODEC_TYPE_2_0); /* 2.0 codec */
#endif /* 1 */

	/*
	 * Drive the ARST# pin low for a minimum of 1uS (as defined in the AC97
	 * spec) and then drive it high.  This is done for non AC97 modes since
	 * there might be logic external to the CS461x that uses the ARST# line
	 * for a reset.
	 */
	csa_writeio(resp, BA0_ACCTL, 1);
	DELAY(50);
	csa_writeio(resp, BA0_ACCTL, 0);
	DELAY(50);
	csa_writeio(resp, BA0_ACCTL, ACCTL_RSTN);

	/*
	 * The first thing we do here is to enable sync generation.  As soon
	 * as we start receiving bit clock, we'll start producing the SYNC
	 * signal.
	 */
	csa_writeio(resp, BA0_ACCTL, ACCTL_ESYN | ACCTL_RSTN);

	/*
	 * Now wait for a short while to allow the AC97 part to start
	 * generating bit clock (so we don't try to start the PLL without an
	 * input clock).
	 */
	DELAY(50000);

	/*
	 * Set the serial port timing configuration, so that
	 * the clock control circuit gets its clock from the correct place.
	 */
	csa_writeio(resp, BA0_SERMC1, SERMC1_PTC_AC97);
	DELAY(700000);

	/*
	 * Write the selected clock control setup to the hardware.  Do not turn on
	 * SWCE yet (if requested), so that the devices clocked by the output of
	 * PLL are not clocked until the PLL is stable.
	 */
	csa_writeio(resp, BA0_PLLCC, PLLCC_LPF_1050_2780_KHZ | PLLCC_CDR_73_104_MHZ);
	csa_writeio(resp, BA0_PLLM, 0x3a);
	csa_writeio(resp, BA0_CLKCR2, CLKCR2_PDIVS_8);

	/*
	 * Power up the PLL.
	 */
	csa_writeio(resp, BA0_CLKCR1, CLKCR1_PLLP);

	/*
	 * Wait until the PLL has stabilized.
	 */
	DELAY(5000);

	/*
	 * Turn on clocking of the core so that we can setup the serial ports.
	 */
	csa_writeio(resp, BA0_CLKCR1, csa_readio(resp, BA0_CLKCR1) | CLKCR1_SWCE);

	/*
	 * Fill the serial port FIFOs with silence.
	 */
	csa_clearserialfifos(resp);

	/*
	 * Set the serial port FIFO pointer to the first sample in the FIFO.
	 */
#ifdef notdef
	csa_writeio(resp, BA0_SERBSP, 0);
#endif /* notdef */

	/*
	 *  Write the serial port configuration to the part.  The master
	 *  enable bit is not set until all other values have been written.
	 */
	csa_writeio(resp, BA0_SERC1, SERC1_SO1F_AC97 | SERC1_SO1EN);
	csa_writeio(resp, BA0_SERC2, SERC2_SI1F_AC97 | SERC1_SO1EN);
	csa_writeio(resp, BA0_SERMC1, SERMC1_PTC_AC97 | SERMC1_MSPE);

	/*
	 * Wait for the codec ready signal from the AC97 codec.
	 */
	acsts = 0;
	for (i = 0 ; i < 1000 ; i++) {
		/*
		 * First, lets wait a short while to let things settle out a bit,
		 * and to prevent retrying the read too quickly.
		 */
		DELAY(125);

		/*
		 * Read the AC97 status register to see if we've seen a CODEC READY
		 * signal from the AC97 codec.
		 */
		acsts = csa_readio(resp, BA0_ACSTS);
		if ((acsts & ACSTS_CRDY) != 0)
			break;
	}

	/*
	 * Make sure we sampled CODEC READY.
	 */
	if ((acsts & ACSTS_CRDY) == 0)
		return (ENXIO);

	/*
	 * Assert the vaid frame signal so that we can start sending commands
	 * to the AC97 codec.
	 */
	csa_writeio(resp, BA0_ACCTL, ACCTL_VFRM | ACCTL_ESYN | ACCTL_RSTN);

	/*
	 * Wait until we've sampled input slots 3 and 4 as valid, meaning that
	 * the codec is pumping ADC data across the AC-link.
	 */
	acisv = 0;
	for (i = 0 ; i < 2000 ; i++) {
		/*
		 * First, lets wait a short while to let things settle out a bit,
		 * and to prevent retrying the read too quickly.
		 */
#ifdef notdef
		DELAY(10000000L); /* clw */
#else
		DELAY(1000);
#endif /* notdef */
		/*
		 * Read the input slot valid register and see if input slots 3 and
		 * 4 are valid yet.
		 */
		acisv = csa_readio(resp, BA0_ACISV);
		if ((acisv & (ACISV_ISV3 | ACISV_ISV4)) == (ACISV_ISV3 | ACISV_ISV4))
			break;
	}
	/*
	 * Make sure we sampled valid input slots 3 and 4.  If not, then return
	 * an error.
	 */
	if ((acisv & (ACISV_ISV3 | ACISV_ISV4)) != (ACISV_ISV3 | ACISV_ISV4))
		return (ENXIO);

	/*
	 * Now, assert valid frame and the slot 3 and 4 valid bits.  This will
	 * commense the transfer of digital audio data to the AC97 codec.
	 */
	csa_writeio(resp, BA0_ACOSV, ACOSV_SLV3 | ACOSV_SLV4);

	/*
	 * Power down the DAC and ADC.  We will power them up (if) when we need
	 * them.
	 */
#ifdef notdef
	csa_writeio(resp, BA0_AC97_POWERDOWN, 0x300);
#endif /* notdef */

	/*
	 * Turn off the Processor by turning off the software clock enable flag in
	 * the clock control register.
	 */
#ifdef notdef
	clkcr1 = csa_readio(resp, BA0_CLKCR1) & ~CLKCR1_SWCE;
	csa_writeio(resp, BA0_CLKCR1, clkcr1);
#endif /* notdef */

	/*
	 * Enable interrupts on the part.
	 */
#if 0
	csa_writeio(resp, BA0_HICR, HICR_IEV | HICR_CHGM);
#endif /* notdef */

	return (0);
}