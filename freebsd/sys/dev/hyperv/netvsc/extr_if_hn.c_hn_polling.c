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
typedef  int /*<<< orphan*/  u_int ;
struct vmbus_channel {int dummy; } ;
struct hn_softc {int hn_rx_ring_inuse; struct vmbus_channel* hn_prichan; } ;

/* Variables and functions */
 int /*<<< orphan*/  HN_LOCK_ASSERT (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_chan_polling (struct vmbus_channel*,int /*<<< orphan*/ ) ; 
 struct vmbus_channel** vmbus_subchan_get (struct vmbus_channel*,int) ; 
 int /*<<< orphan*/  vmbus_subchan_rel (struct vmbus_channel**,int) ; 

__attribute__((used)) static void
hn_polling(struct hn_softc *sc, u_int pollhz)
{
	int nsubch = sc->hn_rx_ring_inuse - 1;

	HN_LOCK_ASSERT(sc);

	if (nsubch > 0) {
		struct vmbus_channel **subch;
		int i;

		subch = vmbus_subchan_get(sc->hn_prichan, nsubch);
		for (i = 0; i < nsubch; ++i)
			hn_chan_polling(subch[i], pollhz);
		vmbus_subchan_rel(subch, nsubch);
	}
	hn_chan_polling(sc->hn_prichan, pollhz);
}