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
typedef  size_t u_int ;
struct sge_fl {size_t cidx; scalar_t__ zone; size_t size; int /*<<< orphan*/  entry_tag; struct rx_sw_desc* sdesc; int /*<<< orphan*/  credits; } ;
struct rx_sw_desc {int flags; int /*<<< orphan*/ * m; int /*<<< orphan*/ * rxsd_cl; int /*<<< orphan*/  map; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_EXT ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int RX_SW_DESC_INUSE ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ zone_mbuf ; 
 scalar_t__ zone_pack ; 

__attribute__((used)) static void
free_rx_bufs(adapter_t *sc, struct sge_fl *q)
{
	u_int cidx = q->cidx;

	while (q->credits--) {
		struct rx_sw_desc *d = &q->sdesc[cidx];

		if (d->flags & RX_SW_DESC_INUSE) {
			bus_dmamap_unload(q->entry_tag, d->map);
			bus_dmamap_destroy(q->entry_tag, d->map);
			if (q->zone == zone_pack) {
				m_init(d->m, M_NOWAIT, MT_DATA, M_EXT);
				uma_zfree(zone_pack, d->m);
			} else {
				m_init(d->m, M_NOWAIT, MT_DATA, 0);
				uma_zfree(zone_mbuf, d->m);
				uma_zfree(q->zone, d->rxsd_cl);
			}			
		}
		
		d->rxsd_cl = NULL;
		d->m = NULL;
		if (++cidx == q->size)
			cidx = 0;
	}
}