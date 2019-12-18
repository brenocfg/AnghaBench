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
struct ucma_file {int dummy; } ;
struct ucma_context {TYPE_1__* cm_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct ucma_context* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct ucma_context*) ; 
 struct ucma_context* ucma_get_ctx (struct ucma_file*,int) ; 
 int /*<<< orphan*/  ucma_put_ctx (struct ucma_context*) ; 

__attribute__((used)) static struct ucma_context *ucma_get_ctx_dev(struct ucma_file *file, int id)
{
	struct ucma_context *ctx = ucma_get_ctx(file, id);

	if (IS_ERR(ctx))
		return ctx;
	if (!ctx->cm_id->device) {
		ucma_put_ctx(ctx);
		return ERR_PTR(-EINVAL);
	}
	return ctx;
}