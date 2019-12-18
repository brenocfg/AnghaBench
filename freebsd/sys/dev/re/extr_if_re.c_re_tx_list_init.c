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
struct TYPE_4__ {int rl_tx_desc_cnt; int rl_tx_free; scalar_t__ rl_tx_considx; scalar_t__ rl_tx_prodidx; int /*<<< orphan*/  rl_tx_list_map; int /*<<< orphan*/  rl_tx_list_tag; struct rl_desc* rl_tx_list; TYPE_1__* rl_tx_desc; } ;
struct rl_softc {TYPE_2__ rl_ldata; } ;
struct rl_desc {int /*<<< orphan*/  rl_cmdstat; } ;
struct TYPE_3__ {int /*<<< orphan*/ * tx_m; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  RL_LOCK_ASSERT (struct rl_softc*) ; 
 int /*<<< orphan*/  RL_TDESC_CMD_EOR ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (struct rl_desc*,int) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  re_netmap_tx_init (struct rl_softc*) ; 

__attribute__((used)) static int
re_tx_list_init(struct rl_softc *sc)
{
	struct rl_desc		*desc;
	int			i;

	RL_LOCK_ASSERT(sc);

	bzero(sc->rl_ldata.rl_tx_list,
	    sc->rl_ldata.rl_tx_desc_cnt * sizeof(struct rl_desc));
	for (i = 0; i < sc->rl_ldata.rl_tx_desc_cnt; i++)
		sc->rl_ldata.rl_tx_desc[i].tx_m = NULL;
#ifdef DEV_NETMAP
	re_netmap_tx_init(sc);
#endif /* DEV_NETMAP */
	/* Set EOR. */
	desc = &sc->rl_ldata.rl_tx_list[sc->rl_ldata.rl_tx_desc_cnt - 1];
	desc->rl_cmdstat |= htole32(RL_TDESC_CMD_EOR);

	bus_dmamap_sync(sc->rl_ldata.rl_tx_list_tag,
	    sc->rl_ldata.rl_tx_list_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	sc->rl_ldata.rl_tx_prodidx = 0;
	sc->rl_ldata.rl_tx_considx = 0;
	sc->rl_ldata.rl_tx_free = sc->rl_ldata.rl_tx_desc_cnt;

	return (0);
}