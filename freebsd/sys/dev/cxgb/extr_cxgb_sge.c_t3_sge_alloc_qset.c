#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_17__ ;
typedef  struct TYPE_21__   TYPE_16__ ;
typedef  struct TYPE_20__   TYPE_15__ ;
typedef  struct TYPE_19__   TYPE_13__ ;

/* Type definitions */
typedef  size_t u_int ;
struct tx_sw_desc {int dummy; } ;
struct tx_desc {int dummy; } ;
struct TYPE_19__ {int gen; int /*<<< orphan*/  holdoff_tmr; int /*<<< orphan*/  cntxt_id; scalar_t__ size; int /*<<< orphan*/  phys_addr; scalar_t__ cidx; int /*<<< orphan*/  lockbuf; int /*<<< orphan*/  lock; int /*<<< orphan*/  desc_map; int /*<<< orphan*/  desc_tag; int /*<<< orphan*/  desc; } ;
struct TYPE_27__ {TYPE_16__* ifp; } ;
struct TYPE_23__ {int enabled; TYPE_5__ ctrl; } ;
struct sge_qset {size_t idx; TYPE_13__ rspq; TYPE_15__* fl; TYPE_2__* txq; TYPE_1__ lro; int /*<<< orphan*/  lock; TYPE_4__* adap; struct port_info* port; int /*<<< orphan*/  namebuf; } ;
struct rx_sw_desc {int dummy; } ;
struct rx_desc {int dummy; } ;
struct rsp_desc {int dummy; } ;
struct qset_params {scalar_t__ jumbo_buf_size; int /*<<< orphan*/  cong_thres; scalar_t__ rspq_size; scalar_t__ jumbo_size; scalar_t__ fl_size; scalar_t__* txq_size; } ;
struct port_info {TYPE_16__* ifp; } ;
struct ifaltq {int dummy; } ;
struct TYPE_25__ {int /*<<< orphan*/  reg_lock; struct sge_qset* qs; } ;
struct TYPE_26__ {TYPE_3__ sge; int /*<<< orphan*/ * tx_dmat; int /*<<< orphan*/  dev; int /*<<< orphan*/ * rx_jumbo_dmat; int /*<<< orphan*/ * rx_dmat; } ;
typedef  TYPE_4__ adapter_t ;
struct TYPE_22__ {size_t c_cpu; } ;
struct TYPE_24__ {int gen; int stop_thres; int /*<<< orphan*/  token; scalar_t__ size; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  qreclaim_task; int /*<<< orphan*/  qresume_task; int /*<<< orphan*/  sendq; int /*<<< orphan*/  entry_tag; int /*<<< orphan*/  desc_map; int /*<<< orphan*/  desc_tag; int /*<<< orphan*/  sdesc; int /*<<< orphan*/  desc; TYPE_17__ txq_watchdog; TYPE_17__ txq_timer; int /*<<< orphan*/ * txq_ifq; int /*<<< orphan*/ * txq_mr; } ;
struct TYPE_21__ {int if_capenable; } ;
struct TYPE_20__ {int gen; scalar_t__ buf_size; scalar_t__ size; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  type; int /*<<< orphan*/  zone; int /*<<< orphan*/  entry_tag; int /*<<< orphan*/  desc_map; int /*<<< orphan*/  desc_tag; int /*<<< orphan*/  sdesc; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_GTS ; 
 int EDOOFUS ; 
 int /*<<< orphan*/  EXT_JUMBO16 ; 
 int /*<<< orphan*/  EXT_JUMBO9 ; 
 int /*<<< orphan*/  EXT_JUMBOP ; 
 int /*<<< orphan*/  EXT_PACKET ; 
 int IFCAP_LRO ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ MCLBYTES ; 
 scalar_t__ MJUM16BYTES ; 
 scalar_t__ MJUM9BYTES ; 
 scalar_t__ MJUMPAGESIZE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RSPQ_NAME_LEN ; 
 int /*<<< orphan*/  SGE_CNTXT_CTRL ; 
 int /*<<< orphan*/  SGE_CNTXT_ETH ; 
 int /*<<< orphan*/  SGE_CNTXT_OFLD ; 
 int SGE_RXQ_PER_SET ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sge_qset*) ; 
 int TXQ_CTRL ; 
 size_t TXQ_ETH ; 
 int /*<<< orphan*/  TXQ_LOCK (struct sge_qset*) ; 
 size_t TXQ_OFLD ; 
 scalar_t__ TX_MAX_SEGS ; 
 int /*<<< orphan*/  USE_GTS ; 
 int V_NEWTIMER (int /*<<< orphan*/ ) ; 
 int V_RSPQ (int /*<<< orphan*/ ) ; 
 int alloc_ring (TYPE_4__*,scalar_t__,int,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * buf_ring_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (TYPE_17__*,int) ; 
 int /*<<< orphan*/  cxgb_txq_buf_ring_size ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int flits_to_desc (scalar_t__) ; 
 int /*<<< orphan*/  ifq_init (int /*<<< orphan*/ *,TYPE_16__*) ; 
 int /*<<< orphan*/  init_qset_cntxt (struct sge_qset*,size_t) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mbufq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t mp_ncpus ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  refill_fl (TYPE_4__*,TYPE_15__*,scalar_t__) ; 
 int /*<<< orphan*/  refill_rspq (TYPE_4__*,TYPE_13__*,scalar_t__) ; 
 int /*<<< orphan*/  restart_ctrlq ; 
 int /*<<< orphan*/  restart_offloadq ; 
 int /*<<< orphan*/  sge_txq_reclaim_handler ; 
 scalar_t__ sgl_len (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  t3_free_qset (TYPE_4__*,struct sge_qset*) ; 
 int t3_sge_init_ecntxt (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int t3_sge_init_flcntxt (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int t3_sge_init_rspcntxt (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_update_qset_coalesce (struct sge_qset*,struct qset_params const*) ; 
 int /*<<< orphan*/  t3_write_reg (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int tcp_lro_init (TYPE_5__*) ; 
 int /*<<< orphan*/  zone_jumbo16 ; 
 int /*<<< orphan*/  zone_jumbo9 ; 
 int /*<<< orphan*/  zone_jumbop ; 
 int /*<<< orphan*/  zone_pack ; 

int
t3_sge_alloc_qset(adapter_t *sc, u_int id, int nports, int irq_vec_idx,
		  const struct qset_params *p, int ntxq, struct port_info *pi)
{
	struct sge_qset *q = &sc->sge.qs[id];
	int i, ret = 0;

	MTX_INIT(&q->lock, q->namebuf, NULL, MTX_DEF);
	q->port = pi;
	q->adap = sc;

	if ((q->txq[TXQ_ETH].txq_mr = buf_ring_alloc(cxgb_txq_buf_ring_size,
	    M_DEVBUF, M_WAITOK, &q->lock)) == NULL) {
		device_printf(sc->dev, "failed to allocate mbuf ring\n");
		goto err;
	}
	if ((q->txq[TXQ_ETH].txq_ifq = malloc(sizeof(struct ifaltq), M_DEVBUF,
	    M_NOWAIT | M_ZERO)) == NULL) {
		device_printf(sc->dev, "failed to allocate ifq\n");
		goto err;
	}
	ifq_init(q->txq[TXQ_ETH].txq_ifq, pi->ifp);	
	callout_init(&q->txq[TXQ_ETH].txq_timer, 1);
	callout_init(&q->txq[TXQ_ETH].txq_watchdog, 1);
	q->txq[TXQ_ETH].txq_timer.c_cpu = id % mp_ncpus;
	q->txq[TXQ_ETH].txq_watchdog.c_cpu = id % mp_ncpus;

	init_qset_cntxt(q, id);
	q->idx = id;
	if ((ret = alloc_ring(sc, p->fl_size, sizeof(struct rx_desc),
		    sizeof(struct rx_sw_desc), &q->fl[0].phys_addr,
		    &q->fl[0].desc, &q->fl[0].sdesc,
		    &q->fl[0].desc_tag, &q->fl[0].desc_map,
		    sc->rx_dmat, &q->fl[0].entry_tag)) != 0) {
		printf("error %d from alloc ring fl0\n", ret);
		goto err;
	}

	if ((ret = alloc_ring(sc, p->jumbo_size, sizeof(struct rx_desc),
		    sizeof(struct rx_sw_desc), &q->fl[1].phys_addr,
		    &q->fl[1].desc, &q->fl[1].sdesc,
		    &q->fl[1].desc_tag, &q->fl[1].desc_map,
		    sc->rx_jumbo_dmat, &q->fl[1].entry_tag)) != 0) {
		printf("error %d from alloc ring fl1\n", ret);
		goto err;
	}

	if ((ret = alloc_ring(sc, p->rspq_size, sizeof(struct rsp_desc), 0,
		    &q->rspq.phys_addr, &q->rspq.desc, NULL,
		    &q->rspq.desc_tag, &q->rspq.desc_map,
		    NULL, NULL)) != 0) {
		printf("error %d from alloc ring rspq\n", ret);
		goto err;
	}

	snprintf(q->rspq.lockbuf, RSPQ_NAME_LEN, "t3 rspq lock %d:%d",
	    device_get_unit(sc->dev), irq_vec_idx);
	MTX_INIT(&q->rspq.lock, q->rspq.lockbuf, NULL, MTX_DEF);

	for (i = 0; i < ntxq; ++i) {
		size_t sz = i == TXQ_CTRL ? 0 : sizeof(struct tx_sw_desc);

		if ((ret = alloc_ring(sc, p->txq_size[i],
			    sizeof(struct tx_desc), sz,
			    &q->txq[i].phys_addr, &q->txq[i].desc,
			    &q->txq[i].sdesc, &q->txq[i].desc_tag,
			    &q->txq[i].desc_map,
			    sc->tx_dmat, &q->txq[i].entry_tag)) != 0) {
			printf("error %d from alloc ring tx %i\n", ret, i);
			goto err;
		}
		mbufq_init(&q->txq[i].sendq, INT_MAX);
		q->txq[i].gen = 1;
		q->txq[i].size = p->txq_size[i];
	}

#ifdef TCP_OFFLOAD
	TASK_INIT(&q->txq[TXQ_OFLD].qresume_task, 0, restart_offloadq, q);
#endif
	TASK_INIT(&q->txq[TXQ_CTRL].qresume_task, 0, restart_ctrlq, q);
	TASK_INIT(&q->txq[TXQ_ETH].qreclaim_task, 0, sge_txq_reclaim_handler, q);
	TASK_INIT(&q->txq[TXQ_OFLD].qreclaim_task, 0, sge_txq_reclaim_handler, q);

	q->fl[0].gen = q->fl[1].gen = 1;
	q->fl[0].size = p->fl_size;
	q->fl[1].size = p->jumbo_size;

	q->rspq.gen = 1;
	q->rspq.cidx = 0;
	q->rspq.size = p->rspq_size;

	q->txq[TXQ_ETH].stop_thres = nports *
	    flits_to_desc(sgl_len(TX_MAX_SEGS + 1) + 3);

	q->fl[0].buf_size = MCLBYTES;
	q->fl[0].zone = zone_pack;
	q->fl[0].type = EXT_PACKET;

	if (p->jumbo_buf_size ==  MJUM16BYTES) {
		q->fl[1].zone = zone_jumbo16;
		q->fl[1].type = EXT_JUMBO16;
	} else if (p->jumbo_buf_size ==  MJUM9BYTES) {
		q->fl[1].zone = zone_jumbo9;
		q->fl[1].type = EXT_JUMBO9;		
	} else if (p->jumbo_buf_size ==  MJUMPAGESIZE) {
		q->fl[1].zone = zone_jumbop;
		q->fl[1].type = EXT_JUMBOP;
	} else {
		KASSERT(0, ("can't deal with jumbo_buf_size %d.", p->jumbo_buf_size));
		ret = EDOOFUS;
		goto err;
	}
	q->fl[1].buf_size = p->jumbo_buf_size;

	/* Allocate and setup the lro_ctrl structure */
	q->lro.enabled = !!(pi->ifp->if_capenable & IFCAP_LRO);
#if defined(INET6) || defined(INET)
	ret = tcp_lro_init(&q->lro.ctrl);
	if (ret) {
		printf("error %d from tcp_lro_init\n", ret);
		goto err;
	}
#endif
	q->lro.ctrl.ifp = pi->ifp;

	mtx_lock_spin(&sc->sge.reg_lock);
	ret = -t3_sge_init_rspcntxt(sc, q->rspq.cntxt_id, irq_vec_idx,
				   q->rspq.phys_addr, q->rspq.size,
				   q->fl[0].buf_size, 1, 0);
	if (ret) {
		printf("error %d from t3_sge_init_rspcntxt\n", ret);
		goto err_unlock;
	}

	for (i = 0; i < SGE_RXQ_PER_SET; ++i) {
		ret = -t3_sge_init_flcntxt(sc, q->fl[i].cntxt_id, 0,
					  q->fl[i].phys_addr, q->fl[i].size,
					  q->fl[i].buf_size, p->cong_thres, 1,
					  0);
		if (ret) {
			printf("error %d from t3_sge_init_flcntxt for index i=%d\n", ret, i);
			goto err_unlock;
		}
	}

	ret = -t3_sge_init_ecntxt(sc, q->txq[TXQ_ETH].cntxt_id, USE_GTS,
				 SGE_CNTXT_ETH, id, q->txq[TXQ_ETH].phys_addr,
				 q->txq[TXQ_ETH].size, q->txq[TXQ_ETH].token,
				 1, 0);
	if (ret) {
		printf("error %d from t3_sge_init_ecntxt\n", ret);
		goto err_unlock;
	}

	if (ntxq > 1) {
		ret = -t3_sge_init_ecntxt(sc, q->txq[TXQ_OFLD].cntxt_id,
					 USE_GTS, SGE_CNTXT_OFLD, id,
					 q->txq[TXQ_OFLD].phys_addr,
					 q->txq[TXQ_OFLD].size, 0, 1, 0);
		if (ret) {
			printf("error %d from t3_sge_init_ecntxt\n", ret);
			goto err_unlock;
		}
	}

	if (ntxq > 2) {
		ret = -t3_sge_init_ecntxt(sc, q->txq[TXQ_CTRL].cntxt_id, 0,
					 SGE_CNTXT_CTRL, id,
					 q->txq[TXQ_CTRL].phys_addr,
					 q->txq[TXQ_CTRL].size,
					 q->txq[TXQ_CTRL].token, 1, 0);
		if (ret) {
			printf("error %d from t3_sge_init_ecntxt\n", ret);
			goto err_unlock;
		}
	}

	mtx_unlock_spin(&sc->sge.reg_lock);
	t3_update_qset_coalesce(q, p);

	refill_fl(sc, &q->fl[0], q->fl[0].size);
	refill_fl(sc, &q->fl[1], q->fl[1].size);
	refill_rspq(sc, &q->rspq, q->rspq.size - 1);

	t3_write_reg(sc, A_SG_GTS, V_RSPQ(q->rspq.cntxt_id) |
		     V_NEWTIMER(q->rspq.holdoff_tmr));

	return (0);

err_unlock:
	mtx_unlock_spin(&sc->sge.reg_lock);
err:	
	TXQ_LOCK(q);
	t3_free_qset(sc, q);

	return (ret);
}