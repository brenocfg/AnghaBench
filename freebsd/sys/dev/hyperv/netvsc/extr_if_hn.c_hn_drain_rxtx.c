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
struct vmbus_channel {int dummy; } ;
struct hn_softc {struct vmbus_channel* hn_prichan; } ;

/* Variables and functions */
 int /*<<< orphan*/  hn_chan_drain (struct hn_softc*,struct vmbus_channel*) ; 
 struct vmbus_channel** vmbus_subchan_get (struct vmbus_channel*,int) ; 
 int /*<<< orphan*/  vmbus_subchan_rel (struct vmbus_channel**,int) ; 

__attribute__((used)) static void
hn_drain_rxtx(struct hn_softc *sc, int nchan)
{
	struct vmbus_channel **subch = NULL;
	int nsubch;

	/*
	 * Drain RX/TX bufrings and interrupts.
	 */
	nsubch = nchan - 1;
	if (nsubch > 0)
		subch = vmbus_subchan_get(sc->hn_prichan, nsubch);

	if (subch != NULL) {
		int i;

		for (i = 0; i < nsubch; ++i)
			hn_chan_drain(sc, subch[i]);
	}
	hn_chan_drain(sc, sc->hn_prichan);

	if (subch != NULL)
		vmbus_subchan_rel(subch, nsubch);
}