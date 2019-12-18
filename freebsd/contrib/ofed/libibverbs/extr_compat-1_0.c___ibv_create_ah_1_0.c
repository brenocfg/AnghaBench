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
struct ibv_ah_attr {int dummy; } ;
struct ibv_ah_1_0 {struct ibv_ah* real_ah; struct ibv_pd_1_0* pd; int /*<<< orphan*/  context; } ;
struct ibv_ah {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ibv_ah_1_0*) ; 
 struct ibv_ah* ibv_create_ah (int /*<<< orphan*/ ,struct ibv_ah_attr*) ; 
 struct ibv_ah_1_0* malloc (int) ; 

struct ibv_ah_1_0 *__ibv_create_ah_1_0(struct ibv_pd_1_0 *pd,
				       struct ibv_ah_attr *attr)
{
	struct ibv_ah *real_ah;
	struct ibv_ah_1_0 *ah;

	ah = malloc(sizeof *ah);
	if (!ah)
		return NULL;

	real_ah = ibv_create_ah(pd->real_pd, attr);
	if (!real_ah) {
		free(ah);
		return NULL;
	}

	ah->context = pd->context;
	ah->pd      = pd;
	ah->real_ah = real_ah;

	return ah;
}