#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  starved; } ;
struct sge_qset {TYPE_3__* fl; TYPE_2__ rspq; } ;
struct TYPE_12__ {int /*<<< orphan*/  rx_fifo_ovfl; } ;
struct cmac {scalar_t__ offset; TYPE_4__ stats; scalar_t__ multiport; } ;
struct port_info {int /*<<< orphan*/  port_id; struct cmac mac; } ;
struct adapter_params {scalar_t__ rev; int nports; } ;
struct TYPE_9__ {struct sge_qset* qs; } ;
struct TYPE_13__ {int flags; scalar_t__ open_device_map; struct port_info* port; struct adapter_params params; TYPE_1__ sge; } ;
typedef  TYPE_5__ adapter_t ;
struct TYPE_11__ {int /*<<< orphan*/  empty; } ;

/* Variables and functions */
 scalar_t__ A_SG_INT_CAUSE ; 
 scalar_t__ A_SG_RSPQ_FL_STATUS ; 
 scalar_t__ A_XGM_INT_CAUSE ; 
 int CXGB_SHUTDOWN ; 
 int FULL_INIT_DONE ; 
 int F_FLEMPTY ; 
 int F_RSPQSTARVE ; 
 int F_RXFIFO_OVERFLOW ; 
 int SGE_QSETS ; 
 scalar_t__ T3_REV_B2 ; 
 int /*<<< orphan*/  check_t3b2_mac (TYPE_5__*) ; 
 int /*<<< orphan*/  cxgb_refresh_stats (struct port_info*) ; 
 int /*<<< orphan*/  isset (scalar_t__*,int /*<<< orphan*/ ) ; 
 int t3_read_reg (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  t3_write_reg (TYPE_5__*,scalar_t__,int) ; 

__attribute__((used)) static void
cxgb_tick_handler(void *arg, int count)
{
	adapter_t *sc = (adapter_t *)arg;
	const struct adapter_params *p = &sc->params;
	int i;
	uint32_t cause, reset;

	if (sc->flags & CXGB_SHUTDOWN || !(sc->flags & FULL_INIT_DONE))
		return;

	if (p->rev == T3_REV_B2 && p->nports < 4 && sc->open_device_map) 
		check_t3b2_mac(sc);

	cause = t3_read_reg(sc, A_SG_INT_CAUSE) & (F_RSPQSTARVE | F_FLEMPTY);
	if (cause) {
		struct sge_qset *qs = &sc->sge.qs[0];
		uint32_t mask, v;

		v = t3_read_reg(sc, A_SG_RSPQ_FL_STATUS) & ~0xff00;

		mask = 1;
		for (i = 0; i < SGE_QSETS; i++) {
			if (v & mask)
				qs[i].rspq.starved++;
			mask <<= 1;
		}

		mask <<= SGE_QSETS; /* skip RSPQXDISABLED */

		for (i = 0; i < SGE_QSETS * 2; i++) {
			if (v & mask) {
				qs[i / 2].fl[i % 2].empty++;
			}
			mask <<= 1;
		}

		/* clear */
		t3_write_reg(sc, A_SG_RSPQ_FL_STATUS, v);
		t3_write_reg(sc, A_SG_INT_CAUSE, cause);
	}

	for (i = 0; i < sc->params.nports; i++) {
		struct port_info *pi = &sc->port[i];
		struct cmac *mac = &pi->mac;

		if (!isset(&sc->open_device_map, pi->port_id))
			continue;

		cxgb_refresh_stats(pi);

		if (mac->multiport)
			continue;

		/* Count rx fifo overflows, once per second */
		cause = t3_read_reg(sc, A_XGM_INT_CAUSE + mac->offset);
		reset = 0;
		if (cause & F_RXFIFO_OVERFLOW) {
			mac->stats.rx_fifo_ovfl++;
			reset |= F_RXFIFO_OVERFLOW;
		}
		t3_write_reg(sc, A_XGM_INT_CAUSE + mac->offset, reset);
	}
}