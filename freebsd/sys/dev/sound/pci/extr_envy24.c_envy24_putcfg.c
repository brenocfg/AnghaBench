#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sc_info {int adcn; int dacn; TYPE_1__* cfg; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int subvendor; int subdevice; int scfg; int acl; int i2s; int spdif; int gpiomask; int gpiodir; int gpiostate; } ;

/* Variables and functions */
 int PCIM_ACL_IMODE ; 
 int PCIM_ACL_MTC ; 
 int PCIM_ACL_OMODE ; 
#define  PCIM_I2S_16BIT 131 
#define  PCIM_I2S_18BIT 130 
#define  PCIM_I2S_20BIT 129 
#define  PCIM_I2S_24BIT 128 
 int PCIM_I2S_96KHZ ; 
 int PCIM_I2S_ID ; 
 int PCIM_I2S_RES ; 
 int PCIM_I2S_VOL ; 
 int PCIM_SCFG_AC97 ; 
 int PCIM_SCFG_MPU ; 
 int PCIM_SCFG_XIN2 ; 
 int PCIM_SPDIF_ID ; 
 int PCIM_SPDIF_IN ; 
 int PCIM_SPDIF_OUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
envy24_putcfg(struct sc_info *sc)
{
	device_printf(sc->dev, "system configuration\n");
	printf("  SubVendorID: 0x%04x, SubDeviceID: 0x%04x\n",
	    sc->cfg->subvendor, sc->cfg->subdevice);
	printf("  XIN2 Clock Source: ");
	switch (sc->cfg->scfg & PCIM_SCFG_XIN2) {
	case 0x00:
		printf("22.5792MHz(44.1kHz*512)\n");
		break;
	case 0x40:
		printf("16.9344MHz(44.1kHz*384)\n");
		break;
	case 0x80:
		printf("from external clock synthesizer chip\n");
		break;
	default:
		printf("illegal system setting\n");
	}
	printf("  MPU-401 UART(s) #: ");
	if (sc->cfg->scfg & PCIM_SCFG_MPU)
		printf("2\n");
	else
		printf("1\n");
	printf("  AC'97 codec: ");
	if (sc->cfg->scfg & PCIM_SCFG_AC97)
		printf("not exist\n");
	else
		printf("exist\n");
	printf("  ADC #: ");
	printf("%d\n", sc->adcn);
	printf("  DAC #: ");
	printf("%d\n", sc->dacn);
	printf("  Multi-track converter type: ");
	if ((sc->cfg->acl & PCIM_ACL_MTC) == 0) {
		printf("AC'97(SDATA_OUT:");
		if (sc->cfg->acl & PCIM_ACL_OMODE)
			printf("packed");
		else
			printf("split");
		printf("|SDATA_IN:");
		if (sc->cfg->acl & PCIM_ACL_IMODE)
			printf("packed");
		else
			printf("split");
		printf(")\n");
	}
	else {
		printf("I2S(");
		if (sc->cfg->i2s & PCIM_I2S_VOL)
			printf("with volume, ");
		if (sc->cfg->i2s & PCIM_I2S_96KHZ)
			printf("96KHz support, ");
		switch (sc->cfg->i2s & PCIM_I2S_RES) {
		case PCIM_I2S_16BIT:
			printf("16bit resolution, ");
			break;
		case PCIM_I2S_18BIT:
			printf("18bit resolution, ");
			break;
		case PCIM_I2S_20BIT:
			printf("20bit resolution, ");
			break;
		case PCIM_I2S_24BIT:
			printf("24bit resolution, ");
			break;
		}
		printf("ID#0x%x)\n", sc->cfg->i2s & PCIM_I2S_ID);
	}
	printf("  S/PDIF(IN/OUT): ");
	if (sc->cfg->spdif & PCIM_SPDIF_IN)
		printf("1/");
	else
		printf("0/");
	if (sc->cfg->spdif & PCIM_SPDIF_OUT)
		printf("1 ");
	else
		printf("0 ");
	if (sc->cfg->spdif & (PCIM_SPDIF_IN | PCIM_SPDIF_OUT))
		printf("ID# 0x%02x\n", (sc->cfg->spdif & PCIM_SPDIF_ID) >> 2);
	printf("  GPIO(mask/dir/state): 0x%02x/0x%02x/0x%02x\n",
	    sc->cfg->gpiomask, sc->cfg->gpiodir, sc->cfg->gpiostate);
}