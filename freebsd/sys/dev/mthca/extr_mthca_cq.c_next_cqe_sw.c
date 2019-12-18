#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mthca_cqe {int dummy; } ;
struct TYPE_2__ {int cqe; } ;
struct mthca_cq {int cons_index; TYPE_1__ ibcq; } ;

/* Variables and functions */
 struct mthca_cqe* cqe_sw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cqe (struct mthca_cq*,int) ; 

__attribute__((used)) static inline struct mthca_cqe *next_cqe_sw(struct mthca_cq *cq)
{
	return cqe_sw(get_cqe(cq, cq->cons_index & cq->ibcq.cqe));
}