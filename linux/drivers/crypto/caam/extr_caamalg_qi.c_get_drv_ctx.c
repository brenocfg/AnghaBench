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
typedef  int /*<<< orphan*/  u32 ;
struct caam_drv_ctx {int op_type; } ;
struct caam_ctx {int /*<<< orphan*/  lock; struct caam_drv_ctx** drv_ctx; int /*<<< orphan*/  qidev; int /*<<< orphan*/ * sh_desc_dec; int /*<<< orphan*/ * sh_desc_enc; } ;
typedef  enum optype { ____Placeholder_optype } optype ;

/* Variables and functions */
 int ENCRYPT ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct caam_drv_ctx*) ; 
 struct caam_drv_ctx* caam_drv_ctx_init (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct caam_drv_ctx *get_drv_ctx(struct caam_ctx *ctx,
					enum optype type)
{
	/*
	 * This function is called on the fast path with values of 'type'
	 * known at compile time. Invalid arguments are not expected and
	 * thus no checks are made.
	 */
	struct caam_drv_ctx *drv_ctx = ctx->drv_ctx[type];
	u32 *desc;

	if (unlikely(!drv_ctx)) {
		spin_lock(&ctx->lock);

		/* Read again to check if some other core init drv_ctx */
		drv_ctx = ctx->drv_ctx[type];
		if (!drv_ctx) {
			int cpu;

			if (type == ENCRYPT)
				desc = ctx->sh_desc_enc;
			else /* (type == DECRYPT) */
				desc = ctx->sh_desc_dec;

			cpu = smp_processor_id();
			drv_ctx = caam_drv_ctx_init(ctx->qidev, &cpu, desc);
			if (!IS_ERR_OR_NULL(drv_ctx))
				drv_ctx->op_type = type;

			ctx->drv_ctx[type] = drv_ctx;
		}

		spin_unlock(&ctx->lock);
	}

	return drv_ctx;
}