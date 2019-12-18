#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct llan_softc {int /*<<< orphan*/  ifp; int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  bus_size_t ;
struct TYPE_3__ {int ds_addr; scalar_t__ ds_len; } ;
typedef  TYPE_1__ bus_dma_segment_t ;
typedef  int /*<<< orphan*/  bufdescs ;

/* Variables and functions */
 int /*<<< orphan*/  H_SEND_LOGICAL_LAN ; 
 int H_SUCCESS ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int LLAN_BUFDESC_VALID ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int phyp_hcall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
llan_send_packet(void *xsc, bus_dma_segment_t *segs, int nsegs,
    bus_size_t mapsize, int error)
{
	struct llan_softc *sc = xsc;
	uint64_t bufdescs[6];
	int i, err;

	bzero(bufdescs, sizeof(bufdescs));

	for (i = 0; i < nsegs; i++) {
		bufdescs[i] = LLAN_BUFDESC_VALID;
		bufdescs[i] |= (((uint64_t)segs[i].ds_len) << 32);
		bufdescs[i] |= segs[i].ds_addr;
	}

	err = phyp_hcall(H_SEND_LOGICAL_LAN, sc->unit, bufdescs[0],
	    bufdescs[1], bufdescs[2], bufdescs[3], bufdescs[4], bufdescs[5], 0);
	/*
	 * The hypercall returning implies completion -- or that the call will
	 * not complete. In principle, we should try a few times if we get back
	 * H_BUSY based on the continuation token in R4. For now, just drop
	 * the packet in such cases.
	 */
	if (err == H_SUCCESS)
		if_inc_counter(sc->ifp, IFCOUNTER_OPACKETS, 1);
	else
		if_inc_counter(sc->ifp, IFCOUNTER_OERRORS, 1);
}