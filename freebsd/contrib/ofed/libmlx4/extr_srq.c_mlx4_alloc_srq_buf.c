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
typedef  int /*<<< orphan*/  uint64_t ;
struct mlx4_wqe_srq_next_seg {int /*<<< orphan*/  next_wqe_index; } ;
struct mlx4_wqe_data_seg {int /*<<< orphan*/  lkey; } ;
struct TYPE_6__ {int /*<<< orphan*/  buf; } ;
struct mlx4_srq {int max; int max_gs; int wqe_shift; int tail; scalar_t__ head; TYPE_3__ buf; int /*<<< orphan*/  wrid; } ;
struct ibv_srq_attr {int dummy; } ;
struct ibv_pd {TYPE_1__* context; } ;
struct TYPE_5__ {int /*<<< orphan*/  page_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_INVALID_LKEY ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 struct mlx4_wqe_srq_next_seg* get_wqe (struct mlx4_srq*,int) ; 
 int /*<<< orphan*/  htobe16 (int) ; 
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mlx4_alloc_buf (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* to_mdev (int /*<<< orphan*/ ) ; 

int mlx4_alloc_srq_buf(struct ibv_pd *pd, struct ibv_srq_attr *attr,
		       struct mlx4_srq *srq)
{
	struct mlx4_wqe_srq_next_seg *next;
	struct mlx4_wqe_data_seg *scatter;
	int size;
	int buf_size;
	int i;

	srq->wrid = malloc(srq->max * sizeof (uint64_t));
	if (!srq->wrid)
		return -1;

	size = sizeof (struct mlx4_wqe_srq_next_seg) +
		srq->max_gs * sizeof (struct mlx4_wqe_data_seg);

	for (srq->wqe_shift = 5; 1 << srq->wqe_shift < size; ++srq->wqe_shift)
		; /* nothing */

	buf_size = srq->max << srq->wqe_shift;

	if (mlx4_alloc_buf(&srq->buf, buf_size,
			   to_mdev(pd->context->device)->page_size)) {
		free(srq->wrid);
		return -1;
	}

	memset(srq->buf.buf, 0, buf_size);

	/*
	 * Now initialize the SRQ buffer so that all of the WQEs are
	 * linked into the list of free WQEs.
	 */

	for (i = 0; i < srq->max; ++i) {
		next = get_wqe(srq, i);
		next->next_wqe_index = htobe16((i + 1) & (srq->max - 1));

		for (scatter = (void *) (next + 1);
		     (void *) scatter < (void *) next + (1 << srq->wqe_shift);
		     ++scatter)
			scatter->lkey = htobe32(MLX4_INVALID_LKEY);
	}

	srq->head = 0;
	srq->tail = srq->max - 1;

	return 0;
}