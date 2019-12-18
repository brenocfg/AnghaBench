#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  status_error; } ;
struct TYPE_6__ {TYPE_2__ upper; } ;
union ixgbe_adv_rx_desc {TYPE_3__ wb; } ;
typedef  size_t uint16_t ;
typedef  int u32 ;
struct rx_ring {union ixgbe_adv_rx_desc* rx_base; } ;
struct ix_rx_queue {struct rx_ring rxr; } ;
struct adapter {TYPE_1__* shared; struct ix_rx_queue* rx_queues; } ;
typedef  int qidx_t ;
struct TYPE_4__ {int* isc_nrxd; } ;

/* Variables and functions */
 int IXGBE_RXD_STAT_DD ; 
 int IXGBE_RXD_STAT_EOP ; 
 int le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixgbe_isc_rxd_available(void *arg, uint16_t qsidx, qidx_t pidx, qidx_t budget)
{
	struct adapter          *sc = arg;
	struct ix_rx_queue      *que = &sc->rx_queues[qsidx];
	struct rx_ring          *rxr = &que->rxr;
	union ixgbe_adv_rx_desc *rxd;
	u32                      staterr;
	int                      cnt, i, nrxd;

	nrxd = sc->shared->isc_nrxd[0];
	for (cnt = 0, i = pidx; cnt < nrxd && cnt <= budget;) {
		rxd = &rxr->rx_base[i];
		staterr = le32toh(rxd->wb.upper.status_error);

		if ((staterr & IXGBE_RXD_STAT_DD) == 0)
			break;
		if (++i == nrxd)
			i = 0;
		if (staterr & IXGBE_RXD_STAT_EOP)
			cnt++;
	}
	return (cnt);
}