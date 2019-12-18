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
struct mlx4_cqe {int dummy; } ;
struct mlx4_cq {int cqe_size; int /*<<< orphan*/  cons_index; } ;

/* Variables and functions */
 int CQ_EMPTY ; 
 int CQ_OK ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct mlx4_cqe*,int) ; 
 struct mlx4_cqe* next_cqe_sw (struct mlx4_cq*) ; 
 int /*<<< orphan*/  udma_from_device_barrier () ; 

__attribute__((used)) static inline int mlx4_get_next_cqe(struct mlx4_cq *cq,
				    struct mlx4_cqe **pcqe)
{
	struct mlx4_cqe *cqe;

	cqe = next_cqe_sw(cq);
	if (!cqe)
		return CQ_EMPTY;

	if (cq->cqe_size == 64)
		++cqe;

	++cq->cons_index;

	VALGRIND_MAKE_MEM_DEFINED(cqe, sizeof *cqe);

	/*
	 * Make sure we read CQ entry contents after we've checked the
	 * ownership bit.
	 */
	udma_from_device_barrier();

	*pcqe = cqe;

	return CQ_OK;
}