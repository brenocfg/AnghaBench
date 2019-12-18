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
typedef  int /*<<< orphan*/  uint32_t ;
struct sdma_conf {scalar_t__ period; } ;
struct sc_pcminfo {struct sc_info* sc; struct sc_chinfo* chan; } ;
struct sc_info {int pos; struct sdma_conf* conf; } ;
struct sc_chinfo {int /*<<< orphan*/  channel; scalar_t__ run; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 int sndbuf_getsize (int /*<<< orphan*/ ) ; 

uint32_t
ssi_dma_intr(void *arg, int chn)
{
	struct sc_pcminfo *scp;
	struct sdma_conf *conf;
	struct sc_chinfo *ch;
	struct sc_info *sc;
	int bufsize;

	scp = arg;
	ch = &scp->chan[0];
	sc = scp->sc;
	conf = sc->conf;

	bufsize = sndbuf_getsize(ch->buffer);

	sc->pos += conf->period;
	if (sc->pos >= bufsize)
		sc->pos -= bufsize;

	if (ch->run)
		chn_intr(ch->channel);

	return (0);
}