#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct xl_list_data {int /*<<< orphan*/  xl_rx_dmamap; int /*<<< orphan*/  xl_rx_tag; TYPE_1__* xl_rx_list; scalar_t__ xl_rx_dmaaddr; } ;
struct xl_chain_data {TYPE_2__* xl_rx_chain; TYPE_2__* xl_rx_head; } ;
struct xl_softc {int /*<<< orphan*/  xl_mtag; struct xl_list_data xl_ldata; struct xl_chain_data xl_cdata; } ;
struct xl_list_onefrag {int dummy; } ;
struct TYPE_4__ {struct TYPE_4__* xl_next; int /*<<< orphan*/  xl_map; TYPE_1__* xl_ptr; } ;
struct TYPE_3__ {int /*<<< orphan*/  xl_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  XL_LOCK_ASSERT (struct xl_softc*) ; 
 int XL_RX_LIST_CNT ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (scalar_t__) ; 
 int xl_newbuf (struct xl_softc*,TYPE_2__*) ; 

__attribute__((used)) static int
xl_list_rx_init(struct xl_softc *sc)
{
	struct xl_chain_data	*cd;
	struct xl_list_data	*ld;
	int			error, i, next;
	u_int32_t		nextptr;

	XL_LOCK_ASSERT(sc);

	cd = &sc->xl_cdata;
	ld = &sc->xl_ldata;

	for (i = 0; i < XL_RX_LIST_CNT; i++) {
		cd->xl_rx_chain[i].xl_ptr = &ld->xl_rx_list[i];
		error = bus_dmamap_create(sc->xl_mtag, 0,
		    &cd->xl_rx_chain[i].xl_map);
		if (error)
			return (error);
		error = xl_newbuf(sc, &cd->xl_rx_chain[i]);
		if (error)
			return (error);
		if (i == (XL_RX_LIST_CNT - 1))
			next = 0;
		else
			next = i + 1;
		nextptr = ld->xl_rx_dmaaddr +
		    next * sizeof(struct xl_list_onefrag);
		cd->xl_rx_chain[i].xl_next = &cd->xl_rx_chain[next];
		ld->xl_rx_list[i].xl_next = htole32(nextptr);
	}

	bus_dmamap_sync(ld->xl_rx_tag, ld->xl_rx_dmamap, BUS_DMASYNC_PREWRITE);
	cd->xl_rx_head = &cd->xl_rx_chain[0];

	return (0);
}