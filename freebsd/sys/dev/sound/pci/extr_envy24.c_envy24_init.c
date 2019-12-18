#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct sc_info {int adcn; int dacn; int /*<<< orphan*/  dev; TYPE_2__* caps; scalar_t__ speed; scalar_t__* intr; scalar_t__* run; int /*<<< orphan*/ * dac; TYPE_3__* cfg; int /*<<< orphan*/ * adc; } ;
struct TYPE_7__ {scalar_t__ subvendor; scalar_t__ subdevice; int scfg; scalar_t__ acl; scalar_t__ i2s; scalar_t__ spdif; TYPE_1__* codec; int /*<<< orphan*/  gpiostate; int /*<<< orphan*/  gpiodir; int /*<<< orphan*/  gpiomask; } ;
struct TYPE_6__ {int /*<<< orphan*/  fmtlist; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* create ) (int /*<<< orphan*/ ,struct sc_info*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  ENVY24_CCS_CTL ; 
 scalar_t__ ENVY24_CCS_CTL_NATIVE ; 
 scalar_t__ ENVY24_CCS_CTL_RESET ; 
 int /*<<< orphan*/  ENVY24_CCS_IMASK ; 
 scalar_t__ ENVY24_CCS_IMASK_PMT ; 
 int /*<<< orphan*/  ENVY24_ROUTE_CLASS_DMA ; 
 int /*<<< orphan*/  ENVY24_ROUTE_CLASS_MIX ; 
 int /*<<< orphan*/  ENVY24_ROUTE_DAC_1 ; 
 int /*<<< orphan*/  ENVY24_ROUTE_DAC_SPDIF ; 
 scalar_t__ PCIM_LAC_DISABLE ; 
 int PCIM_SCFG_ADC ; 
 int PCIM_SCFG_DAC ; 
 int /*<<< orphan*/  PCIR_ACL ; 
 int /*<<< orphan*/  PCIR_I2S ; 
 int /*<<< orphan*/  PCIR_LAC ; 
 int /*<<< orphan*/  PCIR_SCFG ; 
 int /*<<< orphan*/  PCIR_SPDIF ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 TYPE_3__* cfg_table ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ envy24_dmainit (struct sc_info*) ; 
 int /*<<< orphan*/  envy24_gpiosetdir (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  envy24_gpiosetmask (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  envy24_gpiowr (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  envy24_playfmt ; 
 int /*<<< orphan*/  envy24_putcfg (struct sc_info*) ; 
 scalar_t__ envy24_rdcs (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  envy24_recfmt ; 
 TYPE_3__* envy24_rom2cfg (struct sc_info*) ; 
 int /*<<< orphan*/  envy24_route (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  envy24_wrcs (struct sc_info*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ pci_get_subdevice (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subvendor (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
envy24_init(struct sc_info *sc)
{
	u_int32_t data;
#if(0)
	int rtn;
#endif
	int i;
	u_int32_t sv, sd;


#if(0)
	device_printf(sc->dev, "envy24_init()\n");
#endif

	/* reset chip */
	envy24_wrcs(sc, ENVY24_CCS_CTL, ENVY24_CCS_CTL_RESET | ENVY24_CCS_CTL_NATIVE, 1);
	DELAY(200);
	envy24_wrcs(sc, ENVY24_CCS_CTL, ENVY24_CCS_CTL_NATIVE, 1);
	DELAY(200);

	/* legacy hardware disable */
	data = pci_read_config(sc->dev, PCIR_LAC, 2);
	data |= PCIM_LAC_DISABLE;
	pci_write_config(sc->dev, PCIR_LAC, data, 2);

	/* check system configuration */
	sc->cfg = NULL;
	for (i = 0; cfg_table[i].subvendor != 0 || cfg_table[i].subdevice != 0; i++) {
		/* 1st: search configuration from table */
		sv = pci_get_subvendor(sc->dev);
		sd = pci_get_subdevice(sc->dev);
		if (sv == cfg_table[i].subvendor && sd == cfg_table[i].subdevice) {
#if(0)
			device_printf(sc->dev, "Set configuration from table\n");
#endif
			sc->cfg = &cfg_table[i];
			break;
		}
	}
	if (sc->cfg == NULL) {
		/* 2nd: read configuration from table */
		sc->cfg = envy24_rom2cfg(sc);
	}
	sc->adcn = ((sc->cfg->scfg & PCIM_SCFG_ADC) >> 2) + 1;
	sc->dacn = (sc->cfg->scfg & PCIM_SCFG_DAC) + 1;

	if (1 /* bootverbose */) {
		envy24_putcfg(sc);
	}

	/* set system configuration */
	pci_write_config(sc->dev, PCIR_SCFG, sc->cfg->scfg, 1);
	pci_write_config(sc->dev, PCIR_ACL, sc->cfg->acl, 1);
	pci_write_config(sc->dev, PCIR_I2S, sc->cfg->i2s, 1);
	pci_write_config(sc->dev, PCIR_SPDIF, sc->cfg->spdif, 1);
	envy24_gpiosetmask(sc, sc->cfg->gpiomask);
	envy24_gpiosetdir(sc, sc->cfg->gpiodir);
	envy24_gpiowr(sc, sc->cfg->gpiostate);
	for (i = 0; i < sc->adcn; i++) {
		sc->adc[i] = sc->cfg->codec->create(sc->dev, sc, PCMDIR_REC, i);
		sc->cfg->codec->init(sc->adc[i]);
	}
	for (i = 0; i < sc->dacn; i++) {
		sc->dac[i] = sc->cfg->codec->create(sc->dev, sc, PCMDIR_PLAY, i);
		sc->cfg->codec->init(sc->dac[i]);
	}

	/* initialize DMA buffer */
#if(0)
	device_printf(sc->dev, "envy24_init(): initialize DMA buffer\n");
#endif
	if (envy24_dmainit(sc))
		return ENOSPC;

	/* initialize status */
	sc->run[0] = sc->run[1] = 0;
	sc->intr[0] = sc->intr[1] = 0;
	sc->speed = 0;
	sc->caps[0].fmtlist = envy24_playfmt;
	sc->caps[1].fmtlist = envy24_recfmt;

	/* set channel router */
	envy24_route(sc, ENVY24_ROUTE_DAC_1, ENVY24_ROUTE_CLASS_MIX, 0, 0);
	envy24_route(sc, ENVY24_ROUTE_DAC_SPDIF, ENVY24_ROUTE_CLASS_DMA, 0, 0);
	/* envy24_route(sc, ENVY24_ROUTE_DAC_SPDIF, ENVY24_ROUTE_CLASS_MIX, 0, 0); */

	/* set macro interrupt mask */
	data = envy24_rdcs(sc, ENVY24_CCS_IMASK, 1);
	envy24_wrcs(sc, ENVY24_CCS_IMASK, data & ~ENVY24_CCS_IMASK_PMT, 1);
	data = envy24_rdcs(sc, ENVY24_CCS_IMASK, 1);
#if(0)
	device_printf(sc->dev, "envy24_init(): CCS_IMASK-->0x%02x\n", data);
#endif

	return 0;
}