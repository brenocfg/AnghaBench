#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int chip_id; scalar_t__ chip_rev; } ;
struct bhnd_pmu_softc {TYPE_1__ cid; int /*<<< orphan*/  query; } ;
struct TYPE_5__ {int fref; int xf; int p1div; int p2div; int ndiv_frac; int ndiv_int; } ;
typedef  TYPE_2__ pmu1_xtaltab0_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_CCS_HTAVAIL ; 
#define  BHND_CHIPID_BCM4319 134 
#define  BHND_CHIPID_BCM4325 133 
#define  BHND_CHIPID_BCM4329 132 
#define  BHND_CHIPID_BCM4330 131 
#define  BHND_CHIPID_BCM4336 130 
 int /*<<< orphan*/  BHND_PMU1_PLL0_CHIPCTL2 ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC0_BYPASS_SDMOD ; 
 int BHND_PMU1_PLL0_PC0_BYPASS_SDMOD_MASK ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC0_P1DIV ; 
 int BHND_PMU1_PLL0_PC0_P1DIV_MASK ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC0_P2DIV ; 
 int BHND_PMU1_PLL0_PC0_P2DIV_MASK ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC2_NDIV_INT ; 
 int BHND_PMU1_PLL0_PC2_NDIV_INT_MASK ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC2_NDIV_MODE ; 
 int BHND_PMU1_PLL0_PC2_NDIV_MODE_INT ; 
 int BHND_PMU1_PLL0_PC2_NDIV_MODE_MASH ; 
 int BHND_PMU1_PLL0_PC2_NDIV_MODE_MASK ; 
 int BHND_PMU1_PLL0_PC2_NDIV_MODE_MFB ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC3_NDIV_FRAC ; 
 int BHND_PMU1_PLL0_PC3_NDIV_FRAC_MASK ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC4_KVCO_XS ; 
 int BHND_PMU1_PLL0_PC4_KVCO_XS_MASK ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC5_CLK_DRV ; 
 int BHND_PMU1_PLL0_PC5_CLK_DRV_MASK ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC5_PLL_CTRL_37_32 ; 
 int BHND_PMU1_PLL0_PC5_PLL_CTRL_37_32_MASK ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC5_VCO_RNG ; 
 int BHND_PMU1_PLL0_PC5_VCO_RNG_MASK ; 
 int BHND_PMU1_PLL0_PLLCTL0 ; 
 int BHND_PMU1_PLL0_PLLCTL1 ; 
 int BHND_PMU1_PLL0_PLLCTL2 ; 
 int BHND_PMU1_PLL0_PLLCTL3 ; 
 int BHND_PMU1_PLL0_PLLCTL4 ; 
 int BHND_PMU1_PLL0_PLLCTL5 ; 
 int /*<<< orphan*/  BHND_PMU_AND_4 (struct bhnd_pmu_softc*,int,int) ; 
 int BHND_PMU_CCTRL4319USB_24MHZ_PLL_SEL ; 
 int BHND_PMU_CCTRL4319USB_48MHZ_PLL_SEL ; 
 int /*<<< orphan*/  BHND_PMU_CCTRL4319USB_XTAL_SEL ; 
 int /*<<< orphan*/  BHND_PMU_CCTRL4319USB_XTAL_SEL_MASK ; 
 int /*<<< orphan*/  BHND_PMU_CCTRL_WRITE (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int BHND_PMU_CLKSTRETCH ; 
 int BHND_PMU_CTRL ; 
 int BHND_PMU_CTRL_HT_REQ_EN ; 
 int /*<<< orphan*/  BHND_PMU_CTRL_ILP_DIV ; 
 int BHND_PMU_CTRL_ILP_DIV_MASK ; 
 int /*<<< orphan*/  BHND_PMU_CTRL_PLL_PLLCTL_UPD ; 
 int /*<<< orphan*/  BHND_PMU_CTRL_XTALFREQ ; 
 int BHND_PMU_CTRL_XTALFREQ_MASK ; 
 int BHND_PMU_DOT11MAC_880MHZ_CLK_DIVISOR_MASK ; 
 int BHND_PMU_DOT11MAC_880MHZ_CLK_DIVISOR_VAL ; 
 int BHND_PMU_GET_BITS (int,int /*<<< orphan*/ ) ; 
 int BHND_PMU_MAX_RES_MASK ; 
 int BHND_PMU_MIN_RES_MASK ; 
 int /*<<< orphan*/  BHND_PMU_OR_4 (struct bhnd_pmu_softc*,int,int /*<<< orphan*/ ) ; 
 int BHND_PMU_PLL_READ (struct bhnd_pmu_softc*,int) ; 
 int /*<<< orphan*/  BHND_PMU_PLL_WRITE (struct bhnd_pmu_softc*,int,int,int) ; 
 int BHND_PMU_READ_4 (struct bhnd_pmu_softc*,int) ; 
 int BHND_PMU_REV (struct bhnd_pmu_softc*) ; 
 int BHND_PMU_SET_BITS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PMU_WRITE_4 (struct bhnd_pmu_softc*,int,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int PMURES_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMU_DEBUG (struct bhnd_pmu_softc*,char*,...) ; 
 int /*<<< orphan*/  PMU_LOG (struct bhnd_pmu_softc*,char*,int,int) ; 
 int /*<<< orphan*/  PMU_WAIT_CLKST (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RES4319_BBPLL_PWRSW_PU ; 
 int /*<<< orphan*/  RES4319_HT_AVAIL ; 
 int /*<<< orphan*/  RES4325_BBPLL_PWRSW_PU ; 
 int /*<<< orphan*/  RES4325_HT_AVAIL ; 
 int /*<<< orphan*/  RES4329_BBPLL_PWRSW_PU ; 
 int /*<<< orphan*/  RES4329_HT_AVAIL ; 
 int /*<<< orphan*/  RES4330_HT_AVAIL ; 
 int /*<<< orphan*/  RES4330_MACPHY_CLKAVAIL ; 
 int /*<<< orphan*/  RES4336_HT_AVAIL ; 
 int /*<<< orphan*/  RES4336_MACPHY_CLKAVAIL ; 
#define  XTAL_FREQ_24000MHZ 129 
 int XTAL_FREQ_30000MHZ ; 
#define  XTAL_FREQ_48000MHZ 128 
 int bhnd_pmu1_pllfvco0 (int /*<<< orphan*/ *) ; 
 TYPE_2__* bhnd_pmu1_xtaltab0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_pmu_set_4330_plldivs (struct bhnd_pmu_softc*) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static void
bhnd_pmu1_pllinit0(struct bhnd_pmu_softc *sc, uint32_t xtal)
{
	const pmu1_xtaltab0_t		*xt;
	uint32_t			 buf_strength;
	uint32_t			 plladdr, plldata, pllmask;
	uint32_t			 pmuctrl;
	uint32_t			 FVCO;
	uint8_t				 ndiv_mode;

	FVCO = bhnd_pmu1_pllfvco0(&sc->query) / 1000;
	buf_strength = 0;
	ndiv_mode = 1;

	/* Use h/w default PLL config */
	if (xtal == 0) {
		PMU_DEBUG(sc, "Unspecified xtal frequency, skipping PLL "
		    "configuration\n");
		return;
	}

	/* Find the frequency in the table */
	for (xt = bhnd_pmu1_xtaltab0(&sc->query); xt != NULL && xt->fref != 0;
	    xt++)
	{
		if (xt->fref == xtal)
			break;
	}

	/* Check current PLL state, bail out if it has been programmed or
	 * we don't know how to program it.
	 */
	if (xt == NULL || xt->fref == 0) {
		PMU_LOG(sc, "Unsupported XTAL frequency %d.%dMHz, skipping PLL "
		    "configuration\n", xtal / 1000, xtal % 1000);
		return;
	}

	/* For 4319 bootloader already programs the PLL but bootloader does not
	 * program the PLL4 and PLL5. So Skip this check for 4319. */
	pmuctrl = BHND_PMU_READ_4(sc, BHND_PMU_CTRL);
	if (BHND_PMU_GET_BITS(pmuctrl, BHND_PMU_CTRL_XTALFREQ) == xt->xf &&
	    sc->cid.chip_id != BHND_CHIPID_BCM4319 &&
	    sc->cid.chip_id != BHND_CHIPID_BCM4330)
	{   
		PMU_DEBUG(sc, "PLL already programmed for %d.%dMHz\n",
		    xt->fref / 1000, xt->fref % 1000);
		return;
	}

	PMU_DEBUG(sc, "XTAL %d.%dMHz (%d)\n", xtal / 1000, xtal % 1000, xt->xf);
	PMU_DEBUG(sc, "Programming PLL for %d.%dMHz\n", xt->fref / 1000,
		 xt->fref % 1000);

	switch (sc->cid.chip_id) {
	case BHND_CHIPID_BCM4325:
		/* Change the BBPLL drive strength to 2 for all channels */
		buf_strength = 0x222222;

		BHND_PMU_AND_4(sc, BHND_PMU_MIN_RES_MASK,
			~(PMURES_BIT(RES4325_BBPLL_PWRSW_PU) |
			  PMURES_BIT(RES4325_HT_AVAIL)));
		BHND_PMU_AND_4(sc, BHND_PMU_MAX_RES_MASK,
			~(PMURES_BIT(RES4325_BBPLL_PWRSW_PU) |
			  PMURES_BIT(RES4325_HT_AVAIL)));

		/* Wait for HT clock to shutdown. */
		PMU_WAIT_CLKST(sc, 0, BHND_CCS_HTAVAIL);
		break;

	case BHND_CHIPID_BCM4329:
		/* Change the BBPLL drive strength to 8 for all channels */
		buf_strength = 0x888888;

		BHND_PMU_AND_4(sc, BHND_PMU_MIN_RES_MASK,
			~(PMURES_BIT(RES4329_BBPLL_PWRSW_PU) |
			  PMURES_BIT(RES4329_HT_AVAIL)));
		BHND_PMU_AND_4(sc, BHND_PMU_MAX_RES_MASK,
			~(PMURES_BIT(RES4329_BBPLL_PWRSW_PU) |
			  PMURES_BIT(RES4329_HT_AVAIL)));

		/* Wait for HT clock to shutdown. */
		PMU_WAIT_CLKST(sc, 0, BHND_CCS_HTAVAIL);

		/* Initialize PLL4 */
		plladdr = BHND_PMU1_PLL0_PLLCTL4;
		if (xt->fref == 38400)
			plldata = 0x200024C0;
		else if (xt->fref == 37400)
			plldata = 0x20004500;
		else if (xt->fref == 26000)
			plldata = 0x200024C0;
		else
			plldata = 0x200005C0;	/* Chip Dflt Settings */

		BHND_PMU_PLL_WRITE(sc, plladdr, plldata, ~0);

		/* Initialize PLL5 */
		plladdr = BHND_PMU1_PLL0_PLLCTL5;

		plldata = BHND_PMU_PLL_READ(sc, plladdr);
		plldata &= BHND_PMU1_PLL0_PC5_CLK_DRV_MASK;

		if (xt->fref == 38400 ||
		    xt->fref == 37400 || 
		    xt->fref == 26000) {
			plldata |= 0x15;
		} else {
			plldata |= 0x25;	/* Chip Dflt Settings */
		}

		BHND_PMU_PLL_WRITE(sc, plladdr, plldata, ~0);
		break;

	case BHND_CHIPID_BCM4319:
		/* Change the BBPLL drive strength to 2 for all channels */
		buf_strength = 0x222222;

		/* Make sure the PLL is off */
		/* WAR65104: Disable the HT_AVAIL resource first and then
		 * after a delay (more than downtime for HT_AVAIL) remove the
		 * BBPLL resource; backplane clock moves to ALP from HT.
		 */
		BHND_PMU_AND_4(sc, BHND_PMU_MIN_RES_MASK,
			~(PMURES_BIT(RES4319_HT_AVAIL)));
		BHND_PMU_AND_4(sc, BHND_PMU_MAX_RES_MASK,
			~(PMURES_BIT(RES4319_HT_AVAIL)));

		DELAY(100);
		BHND_PMU_AND_4(sc, BHND_PMU_MIN_RES_MASK,
			~(PMURES_BIT(RES4319_BBPLL_PWRSW_PU)));
		BHND_PMU_AND_4(sc, BHND_PMU_MAX_RES_MASK,
			~(PMURES_BIT(RES4319_BBPLL_PWRSW_PU)));

		DELAY(100);

		/* Wait for HT clock to shutdown. */
		PMU_WAIT_CLKST(sc, 0, BHND_CCS_HTAVAIL);

		plldata = 0x200005c0;
		BHND_PMU_PLL_WRITE(sc, BHND_PMU1_PLL0_PLLCTL4, plldata, ~0);
		break;

	case BHND_CHIPID_BCM4336:
		BHND_PMU_AND_4(sc, BHND_PMU_MIN_RES_MASK,
			~(PMURES_BIT(RES4336_HT_AVAIL) |
			  PMURES_BIT(RES4336_MACPHY_CLKAVAIL)));
		BHND_PMU_AND_4(sc, BHND_PMU_MAX_RES_MASK,
			~(PMURES_BIT(RES4336_HT_AVAIL) |
			  PMURES_BIT(RES4336_MACPHY_CLKAVAIL)));
		DELAY(100);

		/* Wait for HT clock to shutdown. */
		PMU_WAIT_CLKST(sc, 0, BHND_CCS_HTAVAIL);

		break;

	case BHND_CHIPID_BCM4330:
		BHND_PMU_AND_4(sc, BHND_PMU_MIN_RES_MASK,
			~(PMURES_BIT(RES4330_HT_AVAIL) |
			  PMURES_BIT(RES4330_MACPHY_CLKAVAIL)));
		BHND_PMU_AND_4(sc, BHND_PMU_MAX_RES_MASK,
			~(PMURES_BIT(RES4330_HT_AVAIL) |
			  PMURES_BIT(RES4330_MACPHY_CLKAVAIL)));
		DELAY(100);

		/* Wait for HT clock to shutdown. */
		PMU_WAIT_CLKST(sc, 0, BHND_CCS_HTAVAIL);

		break;

	default:
		panic("unsupported chipid %#hx\n", sc->cid.chip_id);
	}

	PMU_DEBUG(sc, "Done masking\n");

	/* Write p1div and p2div to pllcontrol[0] */
	plldata = 
	    BHND_PMU_SET_BITS(xt->p1div, BHND_PMU1_PLL0_PC0_P1DIV) |
	    BHND_PMU_SET_BITS(xt->p2div, BHND_PMU1_PLL0_PC0_P2DIV);
	pllmask = BHND_PMU1_PLL0_PC0_P1DIV_MASK|BHND_PMU1_PLL0_PC0_P2DIV_MASK;

	if (sc->cid.chip_id == BHND_CHIPID_BCM4319) {
		plldata &= ~(BHND_PMU1_PLL0_PC0_BYPASS_SDMOD_MASK);
		pllmask |= BHND_PMU1_PLL0_PC0_BYPASS_SDMOD_MASK;
		if (!xt->ndiv_frac) {
			plldata |= BHND_PMU_SET_BITS(1,
			    BHND_PMU1_PLL0_PC0_BYPASS_SDMOD);
		}
	}

	BHND_PMU_PLL_WRITE(sc, BHND_PMU1_PLL0_PLLCTL0, plldata, pllmask);


	if (sc->cid.chip_id == BHND_CHIPID_BCM4330)
		bhnd_pmu_set_4330_plldivs(sc);

	if (sc->cid.chip_id == BHND_CHIPID_BCM4329 && sc->cid.chip_rev == 0) {
		BHND_PMU_PLL_WRITE(sc, BHND_PMU1_PLL0_PLLCTL1,
		    BHND_PMU_DOT11MAC_880MHZ_CLK_DIVISOR_VAL,
		    BHND_PMU_DOT11MAC_880MHZ_CLK_DIVISOR_MASK);
	}

	/* Write ndiv_int and ndiv_mode to pllcontrol[2] */
	if (sc->cid.chip_id == BHND_CHIPID_BCM4336 ||
	    sc->cid.chip_id == BHND_CHIPID_BCM4330)
	{
		ndiv_mode = BHND_PMU1_PLL0_PC2_NDIV_MODE_MFB;
	} else if (sc->cid.chip_id == BHND_CHIPID_BCM4319) {
		if (!(xt->ndiv_frac))
			ndiv_mode = BHND_PMU1_PLL0_PC2_NDIV_MODE_INT;
		else
			ndiv_mode = BHND_PMU1_PLL0_PC2_NDIV_MODE_MFB;
	} else {
		ndiv_mode = BHND_PMU1_PLL0_PC2_NDIV_MODE_MASH;
	}
	

	BHND_PMU_PLL_WRITE(sc, BHND_PMU1_PLL0_PLLCTL2,
	    BHND_PMU_SET_BITS(xt->ndiv_int, BHND_PMU1_PLL0_PC2_NDIV_INT) |
	    BHND_PMU_SET_BITS(ndiv_mode, BHND_PMU1_PLL0_PC2_NDIV_MODE),
	    BHND_PMU1_PLL0_PC2_NDIV_INT_MASK |
	    BHND_PMU1_PLL0_PC2_NDIV_MODE_MASK);

	/* Write ndiv_frac to pllcontrol[3] */
	BHND_PMU_PLL_WRITE(sc, BHND_PMU1_PLL0_PLLCTL3,
	    BHND_PMU_SET_BITS(xt->ndiv_frac, BHND_PMU1_PLL0_PC3_NDIV_FRAC),
	    BHND_PMU1_PLL0_PC3_NDIV_FRAC_MASK);

	/* Writing to pllcontrol[4]  */
	if (sc->cid.chip_id == BHND_CHIPID_BCM4319) {
		uint8_t xs;

		if (!xt->ndiv_frac)
		        plldata = 0x200005c0;
		else
		        plldata = 0x202C2820;

		if (FVCO < 1600)
			xs = 4;
		else
		        xs = 7;

		plldata &= ~(BHND_PMU1_PLL0_PC4_KVCO_XS_MASK);
		plldata |= BHND_PMU_SET_BITS(xs, BHND_PMU1_PLL0_PC4_KVCO_XS);
		BHND_PMU_WRITE_4(sc, BHND_PMU1_PLL0_PLLCTL4, plldata);
	}

	/* Write clock driving strength to pllcontrol[5] */
	if (buf_strength) {
		PMU_DEBUG(sc, "Adjusting PLL buffer drive strength: %x\n",
		    buf_strength);

		plldata = BHND_PMU_SET_BITS(buf_strength,
		    BHND_PMU1_PLL0_PC5_CLK_DRV);
		pllmask = BHND_PMU1_PLL0_PC5_CLK_DRV_MASK;

		if (sc->cid.chip_id == BHND_CHIPID_BCM4319) {
			pllmask |=
			    BHND_PMU1_PLL0_PC5_VCO_RNG_MASK |
			    BHND_PMU1_PLL0_PC5_PLL_CTRL_37_32_MASK;

			if (!xt->ndiv_frac) {
				plldata |= BHND_PMU_SET_BITS(0x25,
				    BHND_PMU1_PLL0_PC5_PLL_CTRL_37_32);
			} else {
				plldata |= BHND_PMU_SET_BITS(0x15,
				    BHND_PMU1_PLL0_PC5_PLL_CTRL_37_32);
			}

			if (FVCO >= 1600) {
				plldata |= BHND_PMU_SET_BITS(0x1,
				    BHND_PMU1_PLL0_PC5_VCO_RNG);
			}
		}

		BHND_PMU_PLL_WRITE(sc, BHND_PMU1_PLL0_PLLCTL5, plldata,
		    pllmask);
	}

	PMU_DEBUG(sc, "Done pll\n");

	/* to operate the 4319 usb in 24MHz/48MHz; chipcontrol[2][84:83] needs
	 * to be updated.
	 */
	if (sc->cid.chip_id == BHND_CHIPID_BCM4319 &&
	    xt->fref != XTAL_FREQ_30000MHZ)
	{
		uint32_t pll_sel;
		
		switch (xt->fref) {
		case XTAL_FREQ_24000MHZ:
			pll_sel = BHND_PMU_CCTRL4319USB_24MHZ_PLL_SEL;
			break;
		case XTAL_FREQ_48000MHZ:
			pll_sel = BHND_PMU_CCTRL4319USB_48MHZ_PLL_SEL;
			break;
		default:
			panic("unsupported 4319USB XTAL frequency: %hu\n",
			    xt->fref);
		}

		BHND_PMU_CCTRL_WRITE(sc, BHND_PMU1_PLL0_CHIPCTL2,
		    BHND_PMU_SET_BITS(pll_sel, BHND_PMU_CCTRL4319USB_XTAL_SEL),
		    BHND_PMU_CCTRL4319USB_XTAL_SEL_MASK);
	}

	/* Flush deferred pll control registers writes */
	if (BHND_PMU_REV(sc) >= 2)
		BHND_PMU_OR_4(sc, BHND_PMU_CTRL, BHND_PMU_CTRL_PLL_PLLCTL_UPD);

	/* Write XtalFreq. Set the divisor also. */
	pmuctrl = BHND_PMU_READ_4(sc, BHND_PMU_CTRL);
	pmuctrl &= ~(BHND_PMU_CTRL_ILP_DIV_MASK | BHND_PMU_CTRL_XTALFREQ_MASK);
	pmuctrl |= BHND_PMU_SET_BITS(((xt->fref + 127) / 128) - 1,
	    BHND_PMU_CTRL_ILP_DIV);
	pmuctrl |= BHND_PMU_SET_BITS(xt->xf, BHND_PMU_CTRL_XTALFREQ);

	if (sc->cid.chip_id == BHND_CHIPID_BCM4329 && sc->cid.chip_rev == 0) {
		/* clear the htstretch before clearing HTReqEn */
		BHND_PMU_AND_4(sc, BHND_PMU_CLKSTRETCH, ~BHND_PMU_CLKSTRETCH);
		pmuctrl &= ~BHND_PMU_CTRL_HT_REQ_EN;
	}

	BHND_PMU_WRITE_4(sc, BHND_PMU_CTRL, pmuctrl);
}