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
typedef  int u_int32_t ;
struct sc_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_MIX_AUXOUT ; 
 int /*<<< orphan*/  AC97_MIX_MASTER ; 
 int /*<<< orphan*/  AC97_REG_POWER ; 
 int /*<<< orphan*/  CS4281PCI_ACCTL ; 
 int CS4281PCI_ACCTL_ESYN ; 
 int CS4281PCI_ACCTL_VFRM ; 
 int /*<<< orphan*/  CS4281PCI_ACISV ; 
 int CS4281PCI_ACISV_ISV (int) ; 
 int /*<<< orphan*/  CS4281PCI_ACOSV ; 
 int CS4281PCI_ACOSV_SLV (int) ; 
 int /*<<< orphan*/  CS4281PCI_ACSTS ; 
 int CS4281PCI_ACSTS_CRDY ; 
 int /*<<< orphan*/  CS4281PCI_CLKCR1 ; 
 int CS4281PCI_CLKCR1_DLLP ; 
 int CS4281PCI_CLKCR1_DLLRDY ; 
 int CS4281PCI_CLKCR1_SWCE ; 
 int /*<<< orphan*/  CS4281PCI_DCR (int /*<<< orphan*/ ) ; 
 int CS4281PCI_DCR_HTCIE ; 
 int CS4281PCI_DCR_MSK ; 
 int CS4281PCI_DCR_TCIE ; 
 int /*<<< orphan*/  CS4281PCI_DMR (int /*<<< orphan*/ ) ; 
 int CS4281PCI_DMR_AUTO ; 
 int CS4281PCI_DMR_DMA ; 
 int CS4281PCI_DMR_TR_PLAY ; 
 int CS4281PCI_DMR_TR_REC ; 
 int /*<<< orphan*/  CS4281PCI_FCR (int /*<<< orphan*/ ) ; 
 int CS4281PCI_FCR_FEN ; 
 int CS4281PCI_FCR_LS (int /*<<< orphan*/ ) ; 
 int CS4281PCI_FCR_OF (scalar_t__) ; 
 int CS4281PCI_FCR_PSH ; 
 int CS4281PCI_FCR_RS (int /*<<< orphan*/ ) ; 
 int CS4281PCI_FCR_SZ (scalar_t__) ; 
 int /*<<< orphan*/  CS4281PCI_HIMR ; 
 int CS4281PCI_HIMR_DMA (int /*<<< orphan*/ ) ; 
 int CS4281PCI_HIMR_DMAI ; 
 int /*<<< orphan*/  CS4281PCI_LPCM_PLAY_SLOT ; 
 int /*<<< orphan*/  CS4281PCI_LPCM_REC_SLOT ; 
 int /*<<< orphan*/  CS4281PCI_PPLVC ; 
 int /*<<< orphan*/  CS4281PCI_PPRVC ; 
 int /*<<< orphan*/  CS4281PCI_RPCM_PLAY_SLOT ; 
 int /*<<< orphan*/  CS4281PCI_RPCM_REC_SLOT ; 
 int /*<<< orphan*/  CS4281PCI_SERMC ; 
 int CS4281PCI_SERMC_PTC_AC97 ; 
 int /*<<< orphan*/  CS4281PCI_SPMC ; 
 int CS4281PCI_SPMC_RSTN ; 
 int /*<<< orphan*/  CS4281PCI_SRCSA ; 
 int CS4281PCI_SRCSA_CLSS (int /*<<< orphan*/ ) ; 
 int CS4281PCI_SRCSA_CRSS (int /*<<< orphan*/ ) ; 
 int CS4281PCI_SRCSA_PLSS (int /*<<< orphan*/ ) ; 
 int CS4281PCI_SRCSA_PRSS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS4281PCI_SSPM ; 
 int CS4281PCI_SSPM_ACLEN ; 
 int CS4281PCI_SSPM_CSRCEN ; 
 int CS4281PCI_SSPM_MIXEN ; 
 int CS4281PCI_SSPM_PSRCEN ; 
 int /*<<< orphan*/  CS4281_DMA_PLAY ; 
 int /*<<< orphan*/  CS4281_DMA_REC ; 
 scalar_t__ CS4281_FIFO_SIZE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  cs4281_clr4 (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int cs4281_rdcd (int /*<<< orphan*/ ,struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4281_set4 (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ cs4281_waitset (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cs4281_wr (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cs4281_wrcd (int /*<<< orphan*/ ,struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
cs4281_init(struct sc_info *sc)
{
    u_int32_t i, v;

    /* (0) Blast clock register and serial port */
    cs4281_wr(sc, CS4281PCI_CLKCR1, 0);
    cs4281_wr(sc, CS4281PCI_SERMC,  0);

    /* (1) Make ESYN 0 to turn sync pulse on AC97 link */
    cs4281_wr(sc, CS4281PCI_ACCTL, 0);
    DELAY(50);

    /* (2) Effect Reset */
    cs4281_wr(sc, CS4281PCI_SPMC, 0);
    DELAY(100);
    cs4281_wr(sc, CS4281PCI_SPMC, CS4281PCI_SPMC_RSTN);
    /* Wait 50ms for ABITCLK to become stable */
    DELAY(50000);

    /* (3) Enable Sound System Clocks */
    cs4281_wr(sc, CS4281PCI_CLKCR1, CS4281PCI_CLKCR1_DLLP);
    DELAY(50000); /* Wait for PLL to stabilize */
    cs4281_wr(sc, CS4281PCI_CLKCR1,
	      CS4281PCI_CLKCR1_DLLP | CS4281PCI_CLKCR1_SWCE);

    /* (4) Power Up - this combination is essential. */
    cs4281_set4(sc, CS4281PCI_SSPM,
		CS4281PCI_SSPM_ACLEN | CS4281PCI_SSPM_PSRCEN |
		CS4281PCI_SSPM_CSRCEN | CS4281PCI_SSPM_MIXEN);

    /* (5) Wait for clock stabilization */
    if (cs4281_waitset(sc,
		       CS4281PCI_CLKCR1,
		       CS4281PCI_CLKCR1_DLLRDY,
		       250) == 0) {
	device_printf(sc->dev, "Clock stabilization failed\n");
	return -1;
    }

    /* (6) Enable ASYNC generation. */
    cs4281_wr(sc, CS4281PCI_ACCTL,CS4281PCI_ACCTL_ESYN);

    /* Wait to allow AC97 to start generating clock bit */
    DELAY(50000);

    /* Set AC97 timing */
    cs4281_wr(sc, CS4281PCI_SERMC, CS4281PCI_SERMC_PTC_AC97);

    /* (7) Wait for AC97 ready signal */
    if (cs4281_waitset(sc, CS4281PCI_ACSTS, CS4281PCI_ACSTS_CRDY, 250) == 0) {
	device_printf(sc->dev, "codec did not avail\n");
	return -1;
    }

    /* (8) Assert valid frame signal to begin sending commands to
     *     AC97 codec */
    cs4281_wr(sc,
	      CS4281PCI_ACCTL,
	      CS4281PCI_ACCTL_VFRM | CS4281PCI_ACCTL_ESYN);

    /* (9) Wait for codec calibration */
    for(i = 0 ; i < 1000; i++) {
	DELAY(10000);
	v = cs4281_rdcd(0, sc, AC97_REG_POWER);
	if ((v & 0x0f) == 0x0f) {
	    break;
	}
    }
    if (i == 1000) {
	device_printf(sc->dev, "codec failed to calibrate\n");
	return -1;
    }

    /* (10) Set AC97 timing */
    cs4281_wr(sc, CS4281PCI_SERMC, CS4281PCI_SERMC_PTC_AC97);

    /* (11) Wait for valid data to arrive */
    if (cs4281_waitset(sc,
		       CS4281PCI_ACISV,
		       CS4281PCI_ACISV_ISV(3) | CS4281PCI_ACISV_ISV(4),
		       10000) == 0) {
	device_printf(sc->dev, "cs4281 never got valid data\n");
	return -1;
    }

    /* (12) Start digital data transfer of audio data to codec */
    cs4281_wr(sc,
	      CS4281PCI_ACOSV,
	      CS4281PCI_ACOSV_SLV(3) | CS4281PCI_ACOSV_SLV(4));

    /* Set Master and headphone to max */
    cs4281_wrcd(0, sc, AC97_MIX_AUXOUT, 0);
    cs4281_wrcd(0, sc, AC97_MIX_MASTER, 0);

    /* Power on the DAC */
    v = cs4281_rdcd(0, sc, AC97_REG_POWER) & 0xfdff;
    cs4281_wrcd(0, sc, AC97_REG_POWER, v);

    /* Wait until DAC state ready */
    for(i = 0; i < 320; i++) {
	DELAY(100);
	v = cs4281_rdcd(0, sc, AC97_REG_POWER);
	if (v & 0x02) break;
    }

    /* Power on the ADC */
    v = cs4281_rdcd(0, sc, AC97_REG_POWER) & 0xfeff;
    cs4281_wrcd(0, sc, AC97_REG_POWER, v);

    /* Wait until ADC state ready */
    for(i = 0; i < 320; i++) {
	DELAY(100);
	v = cs4281_rdcd(0, sc, AC97_REG_POWER);
	if (v & 0x01) break;
    }

    /* FIFO configuration (driver is DMA orientated, implicit FIFO) */
    /* Play FIFO */

    v = CS4281PCI_FCR_RS(CS4281PCI_RPCM_PLAY_SLOT) |
	CS4281PCI_FCR_LS(CS4281PCI_LPCM_PLAY_SLOT) |
	CS4281PCI_FCR_SZ(CS4281_FIFO_SIZE)|
	CS4281PCI_FCR_OF(0);
    cs4281_wr(sc, CS4281PCI_FCR(CS4281_DMA_PLAY), v);

    cs4281_wr(sc, CS4281PCI_FCR(CS4281_DMA_PLAY), v | CS4281PCI_FCR_FEN);

    /* Record FIFO */
    v = CS4281PCI_FCR_RS(CS4281PCI_RPCM_REC_SLOT) |
	CS4281PCI_FCR_LS(CS4281PCI_LPCM_REC_SLOT) |
	CS4281PCI_FCR_SZ(CS4281_FIFO_SIZE)|
	CS4281PCI_FCR_OF(CS4281_FIFO_SIZE + 1);
    cs4281_wr(sc, CS4281PCI_FCR(CS4281_DMA_REC), v | CS4281PCI_FCR_PSH);
    cs4281_wr(sc, CS4281PCI_FCR(CS4281_DMA_REC), v | CS4281PCI_FCR_FEN);

    /* Match AC97 slots to FIFOs */
    v = CS4281PCI_SRCSA_PLSS(CS4281PCI_LPCM_PLAY_SLOT) |
	CS4281PCI_SRCSA_PRSS(CS4281PCI_RPCM_PLAY_SLOT) |
	CS4281PCI_SRCSA_CLSS(CS4281PCI_LPCM_REC_SLOT) |
	CS4281PCI_SRCSA_CRSS(CS4281PCI_RPCM_REC_SLOT);
    cs4281_wr(sc, CS4281PCI_SRCSA, v);

    /* Set Auto-Initialize and set directions */
    cs4281_wr(sc,
	      CS4281PCI_DMR(CS4281_DMA_PLAY),
	      CS4281PCI_DMR_DMA  |
	      CS4281PCI_DMR_AUTO |
	      CS4281PCI_DMR_TR_PLAY);
    cs4281_wr(sc,
	      CS4281PCI_DMR(CS4281_DMA_REC),
	      CS4281PCI_DMR_DMA  |
	      CS4281PCI_DMR_AUTO |
	      CS4281PCI_DMR_TR_REC);

    /* Enable half and empty buffer interrupts keeping DMA paused */
    cs4281_wr(sc,
	      CS4281PCI_DCR(CS4281_DMA_PLAY),
	      CS4281PCI_DCR_TCIE | CS4281PCI_DCR_HTCIE | CS4281PCI_DCR_MSK);
    cs4281_wr(sc,
	      CS4281PCI_DCR(CS4281_DMA_REC),
	      CS4281PCI_DCR_TCIE | CS4281PCI_DCR_HTCIE | CS4281PCI_DCR_MSK);

    /* Enable Interrupts */
    cs4281_clr4(sc,
		CS4281PCI_HIMR,
		CS4281PCI_HIMR_DMAI |
		CS4281PCI_HIMR_DMA(CS4281_DMA_PLAY) |
		CS4281PCI_HIMR_DMA(CS4281_DMA_REC));

    /* Set playback volume */
    cs4281_wr(sc, CS4281PCI_PPLVC, 7);
    cs4281_wr(sc, CS4281PCI_PPRVC, 7);

    return 0;
}