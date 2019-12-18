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
typedef  int /*<<< orphan*/  xdma_transfer_status_t ;
typedef  int /*<<< orphan*/  xdma_channel_t ;
struct xdma_request {scalar_t__ block_len; } ;
struct sc_pcminfo {struct sc_chinfo* chan; struct aic_softc* sc; } ;
struct sc_chinfo {int /*<<< orphan*/  channel; scalar_t__ run; int /*<<< orphan*/  buffer; } ;
struct aic_softc {int pos; int /*<<< orphan*/ * xchan; struct xdma_request req; } ;

/* Variables and functions */
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 int sndbuf_getsize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aic_intr(void *arg, xdma_transfer_status_t *status)
{
	struct sc_pcminfo *scp;
	struct xdma_request *req;
	xdma_channel_t *xchan;
	struct sc_chinfo *ch;
	struct aic_softc *sc;
	int bufsize;

	scp = arg;
	sc = scp->sc;
	ch = &scp->chan[0];
	req = &sc->req;

	xchan = sc->xchan;

	bufsize = sndbuf_getsize(ch->buffer);

	sc->pos += req->block_len;
	if (sc->pos >= bufsize)
		sc->pos -= bufsize;

	if (ch->run)
		chn_intr(ch->channel);

	return (0);
}