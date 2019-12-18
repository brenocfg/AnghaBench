#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int mask; TYPE_5__* info; int /*<<< orphan*/  dmat; } ;
struct TYPE_10__ {int mask; TYPE_3__* info; int /*<<< orphan*/  dmat; } ;
struct TYPE_8__ {int mask; TYPE_1__* info; int /*<<< orphan*/  dmat; } ;
struct mxge_slice_state {TYPE_6__ tx; TYPE_4__ rx_small; TYPE_2__ rx_big; int /*<<< orphan*/  lc; } ;
struct TYPE_11__ {int /*<<< orphan*/ * m; int /*<<< orphan*/  map; scalar_t__ flag; } ;
struct TYPE_9__ {int /*<<< orphan*/ * m; int /*<<< orphan*/  map; } ;
struct TYPE_7__ {int /*<<< orphan*/ * m; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_lro_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mxge_free_slice_mbufs(struct mxge_slice_state *ss)
{
	int i;

#if defined(INET) || defined(INET6)
	tcp_lro_free(&ss->lc);
#endif
	for (i = 0; i <= ss->rx_big.mask; i++) {
		if (ss->rx_big.info[i].m == NULL)
			continue;
		bus_dmamap_unload(ss->rx_big.dmat,
				  ss->rx_big.info[i].map);
		m_freem(ss->rx_big.info[i].m);
		ss->rx_big.info[i].m = NULL;
	}

	for (i = 0; i <= ss->rx_small.mask; i++) {
		if (ss->rx_small.info[i].m == NULL)
			continue;
		bus_dmamap_unload(ss->rx_small.dmat,
				  ss->rx_small.info[i].map);
		m_freem(ss->rx_small.info[i].m);
		ss->rx_small.info[i].m = NULL;
	}

	/* transmit ring used only on the first slice */
	if (ss->tx.info == NULL)
		return;

	for (i = 0; i <= ss->tx.mask; i++) {
		ss->tx.info[i].flag = 0;
		if (ss->tx.info[i].m == NULL)
			continue;
		bus_dmamap_unload(ss->tx.dmat,
				  ss->tx.info[i].map);
		m_freem(ss->tx.info[i].m);
		ss->tx.info[i].m = NULL;
	}
}