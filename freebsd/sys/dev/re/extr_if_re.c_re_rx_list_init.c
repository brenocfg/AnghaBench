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
struct TYPE_4__ {int rl_rx_desc_cnt; scalar_t__ rl_rx_prodidx; int /*<<< orphan*/  rl_rx_list_map; int /*<<< orphan*/  rl_rx_list_tag; TYPE_1__* rl_rx_desc; int /*<<< orphan*/  rl_rx_list; } ;
struct rl_softc {scalar_t__ rl_int_rx_act; int /*<<< orphan*/ * rl_tail; int /*<<< orphan*/  rl_head; TYPE_2__ rl_ldata; } ;
struct rl_desc {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * rx_m; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  re_netmap_rx_init (struct rl_softc*) ; 
 int re_newbuf (struct rl_softc*,int) ; 

__attribute__((used)) static int
re_rx_list_init(struct rl_softc *sc)
{
	int			error, i;

	bzero(sc->rl_ldata.rl_rx_list,
	    sc->rl_ldata.rl_rx_desc_cnt * sizeof(struct rl_desc));
	for (i = 0; i < sc->rl_ldata.rl_rx_desc_cnt; i++) {
		sc->rl_ldata.rl_rx_desc[i].rx_m = NULL;
		if ((error = re_newbuf(sc, i)) != 0)
			return (error);
	}
#ifdef DEV_NETMAP
	re_netmap_rx_init(sc);
#endif /* DEV_NETMAP */

	/* Flush the RX descriptors */

	bus_dmamap_sync(sc->rl_ldata.rl_rx_list_tag,
	    sc->rl_ldata.rl_rx_list_map,
	    BUS_DMASYNC_PREWRITE|BUS_DMASYNC_PREREAD);

	sc->rl_ldata.rl_rx_prodidx = 0;
	sc->rl_head = sc->rl_tail = NULL;
	sc->rl_int_rx_act = 0;

	return (0);
}