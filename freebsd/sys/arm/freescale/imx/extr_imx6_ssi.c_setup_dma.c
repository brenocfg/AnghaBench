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
struct sdma_conf {int word_length; int /*<<< orphan*/  command; int /*<<< orphan*/  num_bd; int /*<<< orphan*/  period; int /*<<< orphan*/  event; scalar_t__ daddr; int /*<<< orphan*/  saddr; struct sc_pcminfo* ih_user; int /*<<< orphan*/  ih; } ;
struct sc_pcminfo {struct sc_info* sc; struct sc_chinfo* chan; } ;
struct sc_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  sdma_ev_tx; int /*<<< orphan*/ * res; int /*<<< orphan*/  buf_base_phys; struct sdma_conf* conf; } ;
struct sc_chinfo {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int AFMT_16BIT ; 
 int AFMT_24BIT ; 
 int /*<<< orphan*/  CMD_2BYTES ; 
 int /*<<< orphan*/  CMD_3BYTES ; 
 scalar_t__ SSI_STX0 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sndbuf_getblkcnt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sndbuf_getblksz (int /*<<< orphan*/ ) ; 
 int sndbuf_getfmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssi_dma_intr ; 

__attribute__((used)) static int
setup_dma(struct sc_pcminfo *scp)
{
	struct sdma_conf *conf;
	struct sc_chinfo *ch;
	struct sc_info *sc;
	int fmt;

	ch = &scp->chan[0];
	sc = scp->sc;
	conf = sc->conf;

	conf->ih = ssi_dma_intr;
	conf->ih_user = scp;
	conf->saddr = sc->buf_base_phys;
	conf->daddr = rman_get_start(sc->res[0]) + SSI_STX0;
	conf->event = sc->sdma_ev_tx; /* SDMA TX event */
	conf->period = sndbuf_getblksz(ch->buffer);
	conf->num_bd = sndbuf_getblkcnt(ch->buffer);

	/*
	 * Word Length
	 * Can be 32, 24, 16 or 8 for sDMA.
	 *
	 * SSI supports 24 at max.
	 */

	fmt = sndbuf_getfmt(ch->buffer);

	if (fmt & AFMT_16BIT) {
		conf->word_length = 16;
		conf->command = CMD_2BYTES;
	} else if (fmt & AFMT_24BIT) {
		conf->word_length = 24;
		conf->command = CMD_3BYTES;
	} else {
		device_printf(sc->dev, "Unknown format\n");
		return (-1);
	}

	return (0);
}