#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {int spu_cfg_RW; } ;
struct TYPE_4__ {int /*<<< orphan*/  register_lock; TYPE_1__ priv2; } ;
struct spu_context {TYPE_2__ csa; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spu_backing_signal1_type_set(struct spu_context *ctx, u64 val)
{
	u64 tmp;

	spin_lock(&ctx->csa.register_lock);
	tmp = ctx->csa.priv2.spu_cfg_RW;
	if (val)
		tmp |= 1;
	else
		tmp &= ~1;
	ctx->csa.priv2.spu_cfg_RW = tmp;
	spin_unlock(&ctx->csa.register_lock);
}