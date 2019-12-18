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
struct sc_pcminfo {struct sc_info* sc; } ;
struct sc_info {int /*<<< orphan*/ * pbuf; int /*<<< orphan*/ * rbuf; } ;
struct sc_chinfo {scalar_t__ dir; int lslot; int rslot; struct sc_pcminfo* parent; } ;

/* Variables and functions */
 int HDSPE_CHANBUF_SAMPLES ; 
 int /*<<< orphan*/  HDSPE_CHANBUF_SIZE ; 
 scalar_t__ PCMDIR_PLAY ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
clean(struct sc_chinfo *ch)
{
	struct sc_pcminfo *scp;
	struct sc_info *sc;
	uint32_t *buf;

	scp = ch->parent;
	sc = scp->sc;
	buf = sc->rbuf;

	if (ch->dir == PCMDIR_PLAY) {
		buf = sc->pbuf;
	}

	bzero(buf + HDSPE_CHANBUF_SAMPLES * ch->lslot, HDSPE_CHANBUF_SIZE);
	bzero(buf + HDSPE_CHANBUF_SAMPLES * ch->rslot, HDSPE_CHANBUF_SIZE);

	return (0);
}