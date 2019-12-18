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
struct ibv_cq_init_attr_ex {int cqe; int comp_vector; int /*<<< orphan*/  wc_flags; struct ibv_comp_channel* channel; } ;
struct ibv_cq_ex {int dummy; } ;
struct ibv_cq {int dummy; } ;
struct ibv_context {int dummy; } ;
struct ibv_comp_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_WC_STANDARD_FLAGS ; 
 struct ibv_cq_ex* create_cq (struct ibv_context*,struct ibv_cq_init_attr_ex*,int /*<<< orphan*/ ) ; 
 struct ibv_cq* ibv_cq_ex_to_cq (struct ibv_cq_ex*) ; 

struct ibv_cq *mlx4_create_cq(struct ibv_context *context, int cqe,
			      struct ibv_comp_channel *channel,
			      int comp_vector)
{
	struct ibv_cq_ex *cq;
	struct ibv_cq_init_attr_ex cq_attr = {.cqe = cqe, .channel = channel,
					      .comp_vector = comp_vector,
					      .wc_flags = IBV_WC_STANDARD_FLAGS};

	cq = create_cq(context, &cq_attr, 0);
	return cq ? ibv_cq_ex_to_cq(cq) : NULL;
}