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
struct TYPE_6__ {int /*<<< orphan*/  ifp; } ;
struct octeon_device {TYPE_3__ props; } ;
struct lio_mbuf_free_info {int /*<<< orphan*/  mb; int /*<<< orphan*/  map; struct lio_gather* g; } ;
struct TYPE_4__ {int q_no; } ;
struct TYPE_5__ {TYPE_1__ s; } ;
struct lio_instr_queue {int /*<<< orphan*/  txtag; struct octeon_device* oct_dev; TYPE_2__ txpciq; } ;
struct lio_gather {int /*<<< orphan*/  node; } ;
struct lio {int /*<<< orphan*/ * glist_lock; int /*<<< orphan*/ * ghead; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 struct lio* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
lio_free_sgmbuf(struct lio_instr_queue *iq, struct lio_mbuf_free_info *finfo)
{
	struct lio_gather	*g;
	struct octeon_device	*oct;
	struct lio		*lio;
	int	iq_no;

	g = finfo->g;
	iq_no = iq->txpciq.s.q_no;
	oct = iq->oct_dev;
	lio = if_getsoftc(oct->props.ifp);

	mtx_lock(&lio->glist_lock[iq_no]);
	STAILQ_INSERT_TAIL(&lio->ghead[iq_no], &g->node, entries);
	mtx_unlock(&lio->glist_lock[iq_no]);

	bus_dmamap_sync(iq->txtag, finfo->map, BUS_DMASYNC_POSTWRITE);
	bus_dmamap_unload(iq->txtag, finfo->map);
	m_freem(finfo->mb);
}