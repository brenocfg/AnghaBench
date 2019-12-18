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
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct snd_queue {int idx; int /*<<< orphan*/  snd_taskq; int /*<<< orphan*/  snd_task; TYPE_2__* snd_buff; int /*<<< orphan*/  snd_buff_dmat; struct nicvf* nic; int /*<<< orphan*/  thresh; int /*<<< orphan*/  free_cnt; scalar_t__ tail; scalar_t__ head; TYPE_1__ dmem; int /*<<< orphan*/  desc; int /*<<< orphan*/ * br; int /*<<< orphan*/  mtx; int /*<<< orphan*/  mtx_name; } ;
struct nicvf {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int MIN_SQ_DESC_PER_PKT_XMIT ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NICVF ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NICVF_SQ_BASE_ALIGN_BYTES ; 
 int /*<<< orphan*/  NICVF_TSO_MAXSIZE ; 
 int /*<<< orphan*/  NICVF_TSO_NSEGS ; 
 int /*<<< orphan*/  NICVF_TX_LOCK (struct snd_queue*) ; 
 int /*<<< orphan*/  NICVF_TX_UNLOCK (struct snd_queue*) ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  SND_QUEUE_DESC_SIZE ; 
 int /*<<< orphan*/  SND_QUEUE_THRESH ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_queue*) ; 
 int /*<<< orphan*/  atomic_store_rel_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * buf_ring_alloc (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nicvf_alloc_q_desc_mem (struct nicvf*,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_snd_task ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int /*<<< orphan*/  taskqueue_create_fast (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

__attribute__((used)) static int
nicvf_init_snd_queue(struct nicvf *nic, struct snd_queue *sq, int q_len,
    int qidx)
{
	size_t i;
	int err;

	/* Initizalize TX lock for this queue */
	snprintf(sq->mtx_name, sizeof(sq->mtx_name), "%s: SQ(%d) lock",
	    device_get_nameunit(nic->dev), qidx);
	mtx_init(&sq->mtx, sq->mtx_name, NULL, MTX_DEF);

	NICVF_TX_LOCK(sq);
	/* Allocate buffer ring */
	sq->br = buf_ring_alloc(q_len / MIN_SQ_DESC_PER_PKT_XMIT, M_DEVBUF,
	    M_NOWAIT, &sq->mtx);
	if (sq->br == NULL) {
		device_printf(nic->dev,
		    "ERROR: Could not set up buf ring for SQ(%d)\n", qidx);
		err = ENOMEM;
		goto error;
	}

	/* Allocate DMA memory for Tx descriptors */
	err = nicvf_alloc_q_desc_mem(nic, &sq->dmem, q_len, SND_QUEUE_DESC_SIZE,
				     NICVF_SQ_BASE_ALIGN_BYTES);
	if (err != 0) {
		device_printf(nic->dev,
		    "Could not allocate DMA memory for SQ\n");
		goto error;
	}

	sq->desc = sq->dmem.base;
	sq->head = sq->tail = 0;
	atomic_store_rel_int(&sq->free_cnt, q_len - 1);
	sq->thresh = SND_QUEUE_THRESH;
	sq->idx = qidx;
	sq->nic = nic;

	/*
	 * Allocate DMA maps for Tx buffers
	 */

	/* Create DMA tag first */
	err = bus_dma_tag_create(
	    bus_get_dma_tag(nic->dev),		/* parent tag */
	    1,					/* alignment */
	    0,					/* boundary */
	    BUS_SPACE_MAXADDR,			/* lowaddr */
	    BUS_SPACE_MAXADDR,			/* highaddr */
	    NULL, NULL,				/* filtfunc, filtfuncarg */
	    NICVF_TSO_MAXSIZE,			/* maxsize */
	    NICVF_TSO_NSEGS,			/* nsegments */
	    MCLBYTES,				/* maxsegsize */
	    0,					/* flags */
	    NULL, NULL,				/* lockfunc, lockfuncarg */
	    &sq->snd_buff_dmat);		/* dmat */

	if (err != 0) {
		device_printf(nic->dev,
		    "Failed to create busdma tag for Tx buffers\n");
		goto error;
	}

	/* Allocate send buffers array */
	sq->snd_buff = malloc(sizeof(*sq->snd_buff) * q_len, M_NICVF,
	    (M_NOWAIT | M_ZERO));
	if (sq->snd_buff == NULL) {
		device_printf(nic->dev,
		    "Could not allocate memory for Tx buffers array\n");
		err = ENOMEM;
		goto error;
	}

	/* Now populate maps */
	for (i = 0; i < q_len; i++) {
		err = bus_dmamap_create(sq->snd_buff_dmat, 0,
		    &sq->snd_buff[i].dmap);
		if (err != 0) {
			device_printf(nic->dev,
			    "Failed to create DMA maps for Tx buffers\n");
			goto error;
		}
	}
	NICVF_TX_UNLOCK(sq);

	/* Allocate taskqueue */
	TASK_INIT(&sq->snd_task, 0, nicvf_snd_task, sq);
	sq->snd_taskq = taskqueue_create_fast("nicvf_snd_taskq", M_WAITOK,
	    taskqueue_thread_enqueue, &sq->snd_taskq);
	taskqueue_start_threads(&sq->snd_taskq, 1, PI_NET, "%s: snd_taskq(%d)",
	    device_get_nameunit(nic->dev), qidx);

	return (0);
error:
	NICVF_TX_UNLOCK(sq);
	return (err);
}