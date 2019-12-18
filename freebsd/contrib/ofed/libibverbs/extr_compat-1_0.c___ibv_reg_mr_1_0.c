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
struct ibv_pd_1_0 {int /*<<< orphan*/  context; int /*<<< orphan*/  real_pd; } ;
struct ibv_mr_1_0 {struct ibv_mr* real_mr; int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; struct ibv_pd_1_0* pd; int /*<<< orphan*/  context; } ;
struct ibv_mr {int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ibv_mr_1_0*) ; 
 struct ibv_mr* ibv_reg_mr (int /*<<< orphan*/ ,void*,size_t,int) ; 
 struct ibv_mr_1_0* malloc (int) ; 

struct ibv_mr_1_0 *__ibv_reg_mr_1_0(struct ibv_pd_1_0 *pd, void *addr,
				    size_t length, int access)
{
	struct ibv_mr *real_mr;
	struct ibv_mr_1_0 *mr;

	mr = malloc(sizeof *mr);
	if (!mr)
		return NULL;

	real_mr = ibv_reg_mr(pd->real_pd, addr, length, access);
	if (!real_mr) {
		free(mr);
		return NULL;
	}

	mr->context = pd->context;
	mr->pd      = pd;
	mr->lkey    = real_mr->lkey;
	mr->rkey    = real_mr->rkey;
	mr->real_mr = real_mr;

	return mr;
}