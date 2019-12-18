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
struct verbs_context {TYPE_1__* priv; } ;
struct ibv_cq_init_attr_ex {int wc_flags; int /*<<< orphan*/  cq_context; int /*<<< orphan*/  channel; } ;
struct ibv_cq_ex {int dummy; } ;
struct ibv_context {int dummy; } ;
struct TYPE_2__ {struct ibv_cq_ex* (* create_cq_ex ) (struct ibv_context*,struct ibv_cq_init_attr_ex*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int IBV_CREATE_CQ_SUP_WC_FLAGS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ibv_cq_ex_to_cq (struct ibv_cq_ex*) ; 
 struct ibv_cq_ex* stub1 (struct ibv_context*,struct ibv_cq_init_attr_ex*) ; 
 struct verbs_context* verbs_get_ctx (struct ibv_context*) ; 
 int /*<<< orphan*/  verbs_init_cq (int /*<<< orphan*/ ,struct ibv_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ibv_cq_ex *
__lib_ibv_create_cq_ex(struct ibv_context *context,
		       struct ibv_cq_init_attr_ex *cq_attr)
{
	struct verbs_context *vctx = verbs_get_ctx(context);
	struct ibv_cq_ex *cq;

	if (cq_attr->wc_flags & ~IBV_CREATE_CQ_SUP_WC_FLAGS) {
		errno = EOPNOTSUPP;
		return NULL;
	}

	cq = vctx->priv->create_cq_ex(context, cq_attr);

	if (cq)
		verbs_init_cq(ibv_cq_ex_to_cq(cq), context,
			        cq_attr->channel, cq_attr->cq_context);

	return cq;
}