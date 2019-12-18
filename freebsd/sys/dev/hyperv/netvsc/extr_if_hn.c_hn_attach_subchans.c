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
struct hn_softc {int hn_rx_ring_inuse; int /*<<< orphan*/  hn_ifp; int /*<<< orphan*/  hn_prichan; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ bootverbose ; 
 int hn_chan_attach (struct hn_softc*,struct vmbus_channel*) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,int) ; 
 struct vmbus_channel** vmbus_subchan_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmbus_subchan_rel (struct vmbus_channel**,int) ; 

__attribute__((used)) static int
hn_attach_subchans(struct hn_softc *sc)
{
	struct vmbus_channel **subchans;
	int subchan_cnt = sc->hn_rx_ring_inuse - 1;
	int i, error = 0;

	KASSERT(subchan_cnt > 0, ("no sub-channels"));

	/* Attach the sub-channels. */
	subchans = vmbus_subchan_get(sc->hn_prichan, subchan_cnt);
	for (i = 0; i < subchan_cnt; ++i) {
		int error1;

		error1 = hn_chan_attach(sc, subchans[i]);
		if (error1) {
			error = error1;
			/* Move on; all channels will be detached later. */
		}
	}
	vmbus_subchan_rel(subchans, subchan_cnt);

	if (error) {
		if_printf(sc->hn_ifp, "sub-channels attach failed: %d\n", error);
	} else {
		if (bootverbose) {
			if_printf(sc->hn_ifp, "%d sub-channels attached\n",
			    subchan_cnt);
		}
	}
	return (error);
}