#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ link_ok; } ;
struct TYPE_8__ {TYPE_1__* ops; } ;
struct TYPE_7__ {scalar_t__ offset; } ;
struct port_info {struct adapter* adapter; int /*<<< orphan*/  port_id; TYPE_2__ link_config; TYPE_4__ phy; TYPE_3__ mac; int /*<<< orphan*/  link_check_task; int /*<<< orphan*/  link_check_ch; struct ifnet* ifp; } ;
struct ifnet {int if_drv_flags; } ;
struct adapter {scalar_t__ open_device_map; int /*<<< orphan*/  tq; int /*<<< orphan*/  tick_task; int /*<<< orphan*/  slow_intr_task; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* power_down ) (TYPE_4__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_LOCK_ASSERT_NOTOWNED (struct adapter*) ; 
 scalar_t__ A_XGM_RXFIFO_CFG ; 
 scalar_t__ A_XGM_TXFIFO_CFG ; 
 scalar_t__ A_XGM_TX_CFG ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  F_TXFIFO_EMPTY ; 
 int /*<<< orphan*/  F_TXPAUSEEN ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MAC_DIRECTION_RX ; 
 int /*<<< orphan*/  M_RXFIFOPAUSEHWM ; 
 int /*<<< orphan*/  PORT_LOCK (struct port_info*) ; 
 int /*<<< orphan*/  PORT_UNLOCK (struct port_info*) ; 
 int /*<<< orphan*/  V_RXFIFOPAUSEHWM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clrbit (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb_down (struct adapter*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  t3_mac_disable (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_os_link_changed (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_port_intr_disable (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_set_reg_field (struct adapter*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_wait_op_done (struct adapter*,scalar_t__,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cxgb_uninit_synchronized(struct port_info *pi)
{
	struct adapter *sc = pi->adapter;
	struct ifnet *ifp = pi->ifp;

	/*
	 * taskqueue_drain may cause a deadlock if the adapter lock is held.
	 */
	ADAPTER_LOCK_ASSERT_NOTOWNED(sc);

	/*
	 * Clear this port's bit from the open device map, and then drain all
	 * the tasks that can access/manipulate this port's port_info or ifp.
	 * We disable this port's interrupts here and so the slow/ext
	 * interrupt tasks won't be enqueued.  The tick task will continue to
	 * be enqueued every second but the runs after this drain will not see
	 * this port in the open device map.
	 *
	 * A well behaved task must take open_device_map into account and ignore
	 * ports that are not open.
	 */
	clrbit(&sc->open_device_map, pi->port_id);
	t3_port_intr_disable(sc, pi->port_id);
	taskqueue_drain(sc->tq, &sc->slow_intr_task);
	taskqueue_drain(sc->tq, &sc->tick_task);

	callout_drain(&pi->link_check_ch);
	taskqueue_drain(sc->tq, &pi->link_check_task);

	PORT_LOCK(pi);
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);

	/* disable pause frames */
	t3_set_reg_field(sc, A_XGM_TX_CFG + pi->mac.offset, F_TXPAUSEEN, 0);

	/* Reset RX FIFO HWM */
	t3_set_reg_field(sc, A_XGM_RXFIFO_CFG +  pi->mac.offset,
			 V_RXFIFOPAUSEHWM(M_RXFIFOPAUSEHWM), 0);

	DELAY(100 * 1000);

	/* Wait for TXFIFO empty */
	t3_wait_op_done(sc, A_XGM_TXFIFO_CFG + pi->mac.offset,
			F_TXFIFO_EMPTY, 1, 20, 5);

	DELAY(100 * 1000);
	t3_mac_disable(&pi->mac, MAC_DIRECTION_RX);

	pi->phy.ops->power_down(&pi->phy, 1);

	PORT_UNLOCK(pi);

	pi->link_config.link_ok = 0;
	t3_os_link_changed(sc, pi->port_id, 0, 0, 0, 0, 0);

	if (sc->open_device_map == 0)
		cxgb_down(pi->adapter);

	return (0);
}