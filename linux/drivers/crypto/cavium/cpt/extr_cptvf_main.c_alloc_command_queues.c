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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cpt_vf {int qsize; int nr_queues; struct pci_dev* pdev; } ;
struct command_queue {scalar_t__ nchunks; int /*<<< orphan*/  lock; struct command_chunk* qhead; int /*<<< orphan*/  chead; } ;
struct command_qinfo {size_t cmd_size; size_t qchunksize; struct command_queue* queue; } ;
struct command_chunk {size_t size; scalar_t__ dma_addr; int /*<<< orphan*/ * head; int /*<<< orphan*/  nextchunk; } ;

/* Variables and functions */
 int CPT_NEXT_CHUNK_PTR_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,scalar_t__) ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,size_t,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_command_queues (struct cpt_vf*,struct command_qinfo*) ; 
 int /*<<< orphan*/  hlist_add_behind (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct command_chunk*) ; 
 struct command_chunk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int min (size_t,size_t) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alloc_command_queues(struct cpt_vf *cptvf,
				struct command_qinfo *cqinfo, size_t cmd_size,
				u32 qlen)
{
	int i;
	size_t q_size;
	struct command_queue *queue = NULL;
	struct pci_dev *pdev = cptvf->pdev;

	/* common init */
	cqinfo->cmd_size = cmd_size;
	/* Qsize in dwords, needed for SADDR config, 1-next chunk pointer */
	cptvf->qsize = min(qlen, cqinfo->qchunksize) *
			CPT_NEXT_CHUNK_PTR_SIZE + 1;
	/* Qsize in bytes to create space for alignment */
	q_size = qlen * cqinfo->cmd_size;

	/* per queue initialization */
	for (i = 0; i < cptvf->nr_queues; i++) {
		size_t c_size = 0;
		size_t rem_q_size = q_size;
		struct command_chunk *curr = NULL, *first = NULL, *last = NULL;
		u32 qcsize_bytes = cqinfo->qchunksize * cqinfo->cmd_size;

		queue = &cqinfo->queue[i];
		INIT_HLIST_HEAD(&cqinfo->queue[i].chead);
		do {
			curr = kzalloc(sizeof(*curr), GFP_KERNEL);
			if (!curr)
				goto cmd_qfail;

			c_size = (rem_q_size > qcsize_bytes) ? qcsize_bytes :
					rem_q_size;
			curr->head = (u8 *)dma_alloc_coherent(&pdev->dev,
							      c_size + CPT_NEXT_CHUNK_PTR_SIZE,
							      &curr->dma_addr,
							      GFP_KERNEL);
			if (!curr->head) {
				dev_err(&pdev->dev, "Command Q (%d) chunk (%d) allocation failed\n",
					i, queue->nchunks);
				kfree(curr);
				goto cmd_qfail;
			}

			curr->size = c_size;
			if (queue->nchunks == 0) {
				hlist_add_head(&curr->nextchunk,
					       &cqinfo->queue[i].chead);
				first = curr;
			} else {
				hlist_add_behind(&curr->nextchunk,
						 &last->nextchunk);
			}

			queue->nchunks++;
			rem_q_size -= c_size;
			if (last)
				*((u64 *)(&last->head[last->size])) = (u64)curr->dma_addr;

			last = curr;
		} while (rem_q_size);

		/* Make the queue circular */
		/* Tie back last chunk entry to head */
		curr = first;
		*((u64 *)(&last->head[last->size])) = (u64)curr->dma_addr;
		queue->qhead = curr;
		spin_lock_init(&queue->lock);
	}
	return 0;

cmd_qfail:
	free_command_queues(cptvf, cqinfo);
	return -ENOMEM;
}