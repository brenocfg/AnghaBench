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
struct hn_softc {int /*<<< orphan*/  hn_prichan; int /*<<< orphan*/  hn_ifp; } ;

/* Variables and functions */
 scalar_t__ bootverbose ; 
 int hn_nvs_alloc_subchans (struct hn_softc*,int*) ; 
 int hn_rndis_query_rsscaps (struct hn_softc*,int*) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct vmbus_channel** vmbus_subchan_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmbus_subchan_rel (struct vmbus_channel**,int) ; 

__attribute__((used)) static int
hn_synth_alloc_subchans(struct hn_softc *sc, int *nsubch)
{
	struct vmbus_channel **subchans;
	int nchan, rxr_cnt, error;

	nchan = *nsubch + 1;
	if (nchan == 1) {
		/*
		 * Multiple RX/TX rings are not requested.
		 */
		*nsubch = 0;
		return (0);
	}

	/*
	 * Query RSS capabilities, e.g. # of RX rings, and # of indirect
	 * table entries.
	 */
	error = hn_rndis_query_rsscaps(sc, &rxr_cnt);
	if (error) {
		/* No RSS; this is benign. */
		*nsubch = 0;
		return (0);
	}
	if (bootverbose) {
		if_printf(sc->hn_ifp, "RX rings offered %u, requested %d\n",
		    rxr_cnt, nchan);
	}

	if (nchan > rxr_cnt)
		nchan = rxr_cnt;
	if (nchan == 1) {
		if_printf(sc->hn_ifp, "only 1 channel is supported, no vRSS\n");
		*nsubch = 0;
		return (0);
	}

	/*
	 * Allocate sub-channels from NVS.
	 */
	*nsubch = nchan - 1;
	error = hn_nvs_alloc_subchans(sc, nsubch);
	if (error || *nsubch == 0) {
		/* Failed to allocate sub-channels. */
		*nsubch = 0;
		return (0);
	}

	/*
	 * Wait for all sub-channels to become ready before moving on.
	 */
	subchans = vmbus_subchan_get(sc->hn_prichan, *nsubch);
	vmbus_subchan_rel(subchans, *nsubch);
	return (0);
}