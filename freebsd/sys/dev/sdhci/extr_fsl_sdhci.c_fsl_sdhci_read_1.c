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
struct sdhci_slot {int dummy; } ;
struct fsl_sdhci_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int bus_size_t ;

/* Variables and functions */
 int RD4 (struct fsl_sdhci_softc*,int) ; 
 int SDHCI_CTRL_4BITBUS ; 
 int SDHCI_CTRL_8BITBUS ; 
 int SDHCI_CTRL_ADMA2 ; 
 int SDHCI_CTRL_ADMA264 ; 
 int SDHCI_CTRL_CARD_DET ; 
 int SDHCI_CTRL_FORCE_CARD ; 
 int SDHCI_CTRL_LED ; 
 int SDHCI_HOST_CONTROL ; 
 int SDHCI_POWER_300 ; 
 int SDHCI_POWER_CONTROL ; 
 int SDHCI_POWER_ON ; 
#define  SDHC_PROT_ADMA1 134 
#define  SDHC_PROT_ADMA2 133 
#define  SDHC_PROT_ADMA264 132 
 int SDHC_PROT_CTRL ; 
 int SDHC_PROT_DMA_MASK ; 
#define  SDHC_PROT_SDMA 131 
#define  SDHC_PROT_WIDTH_1BIT 130 
#define  SDHC_PROT_WIDTH_4BIT 129 
#define  SDHC_PROT_WIDTH_8BIT 128 
 int SDHC_PROT_WIDTH_MASK ; 
 struct fsl_sdhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
fsl_sdhci_read_1(device_t dev, struct sdhci_slot *slot, bus_size_t off)
{
	struct fsl_sdhci_softc *sc = device_get_softc(dev);
	uint32_t val32, wrk32;

	/*
	 * Most of the things in the standard host control register are in the
	 * hardware's wider protocol control register, but some of the bits are
	 * moved around.
	 */
	if (off == SDHCI_HOST_CONTROL) {
		wrk32 = RD4(sc, SDHC_PROT_CTRL);
		val32 = wrk32 & (SDHCI_CTRL_LED | SDHCI_CTRL_CARD_DET |
		    SDHCI_CTRL_FORCE_CARD);
		switch (wrk32 & SDHC_PROT_WIDTH_MASK) {
		case SDHC_PROT_WIDTH_1BIT:
			/* Value is already 0. */
			break;
		case SDHC_PROT_WIDTH_4BIT:
			val32 |= SDHCI_CTRL_4BITBUS;
			break;
		case SDHC_PROT_WIDTH_8BIT:
			val32 |= SDHCI_CTRL_8BITBUS;
			break;
		}
		switch (wrk32 & SDHC_PROT_DMA_MASK) {
		case SDHC_PROT_SDMA:
			/* Value is already 0. */
			break;
		case SDHC_PROT_ADMA1:
			/* This value is deprecated, should never appear. */
			break;
		case SDHC_PROT_ADMA2:
			val32 |= SDHCI_CTRL_ADMA2;
			break;
		case SDHC_PROT_ADMA264:
			val32 |= SDHCI_CTRL_ADMA264;
			break;
		}
		return val32;
	}

	/*
	 * XXX can't find the bus power on/off knob.  For now we have to say the
	 * power is always on and always set to the same voltage.
	 */
	if (off == SDHCI_POWER_CONTROL) {
		return (SDHCI_POWER_ON | SDHCI_POWER_300);
	}


	return ((RD4(sc, off & ~3) >> (off & 3) * 8) & 0xff);
}