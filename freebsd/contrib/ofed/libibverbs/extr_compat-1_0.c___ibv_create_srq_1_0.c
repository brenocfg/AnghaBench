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
struct ibv_srq_init_attr {int /*<<< orphan*/  srq_context; } ;
struct ibv_srq_1_0 {struct ibv_srq* real_srq; struct ibv_pd_1_0* pd; int /*<<< orphan*/  srq_context; int /*<<< orphan*/  context; } ;
struct ibv_srq {struct ibv_srq_1_0* srq_context; } ;
struct ibv_pd_1_0 {int /*<<< orphan*/  context; int /*<<< orphan*/  real_pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ibv_srq_1_0*) ; 
 struct ibv_srq* ibv_create_srq (int /*<<< orphan*/ ,struct ibv_srq_init_attr*) ; 
 struct ibv_srq_1_0* malloc (int) ; 

struct ibv_srq_1_0 *__ibv_create_srq_1_0(struct ibv_pd_1_0 *pd,
					 struct ibv_srq_init_attr *srq_init_attr)
{
	struct ibv_srq *real_srq;
	struct ibv_srq_1_0 *srq;

	srq = malloc(sizeof *srq);
	if (!srq)
		return NULL;

	real_srq = ibv_create_srq(pd->real_pd, srq_init_attr);
	if (!real_srq) {
		free(srq);
		return NULL;
	}

	srq->context     = pd->context;
	srq->srq_context = srq_init_attr->srq_context;
	srq->pd          = pd;
	srq->real_srq    = real_srq;

	real_srq->srq_context = srq;

	return srq;
}