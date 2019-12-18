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
typedef  int uint32_t ;
struct TYPE_4__ {int rl_rx_desc_cnt; struct rl_desc* rl_rx_list; struct rl_rxdesc* rl_rx_desc; struct rl_rxdesc* rl_jrx_desc; } ;
struct rl_softc {int rl_flags; TYPE_2__ rl_ldata; TYPE_1__* rl_ifp; } ;
struct rl_rxdesc {int rx_size; } ;
struct rl_desc {int /*<<< orphan*/  rl_cmdstat; scalar_t__ rl_vlanctl; } ;
struct TYPE_3__ {scalar_t__ if_mtu; } ;

/* Variables and functions */
 int RL_FLAG_JUMBOV2 ; 
 scalar_t__ RL_MTU ; 
 int RL_RDESC_CMD_EOR ; 
 int RL_RDESC_CMD_OWN ; 
 int /*<<< orphan*/  htole32 (int) ; 

__attribute__((used)) static __inline void
re_discard_rxbuf(struct rl_softc *sc, int idx)
{
	struct rl_desc		*desc;
	struct rl_rxdesc	*rxd;
	uint32_t		cmdstat;

	if (sc->rl_ifp->if_mtu > RL_MTU &&
	    (sc->rl_flags & RL_FLAG_JUMBOV2) != 0)
		rxd = &sc->rl_ldata.rl_jrx_desc[idx];
	else
		rxd = &sc->rl_ldata.rl_rx_desc[idx];
	desc = &sc->rl_ldata.rl_rx_list[idx];
	desc->rl_vlanctl = 0;
	cmdstat = rxd->rx_size;
	if (idx == sc->rl_ldata.rl_rx_desc_cnt - 1)
		cmdstat |= RL_RDESC_CMD_EOR;
	desc->rl_cmdstat = htole32(cmdstat | RL_RDESC_CMD_OWN);
}