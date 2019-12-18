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
typedef  int u64 ;
struct TYPE_2__ {int mfc_sr1_RW; } ;
struct spu_state {int /*<<< orphan*/  register_lock; TYPE_1__ priv1; } ;
struct spu_context {struct spu_state csa; } ;

/* Variables and functions */
 int MFC_STATE1_MASTER_RUN_CONTROL_MASK ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spu_backing_master_start(struct spu_context *ctx)
{
	struct spu_state *csa = &ctx->csa;
	u64 sr1;

	spin_lock(&csa->register_lock);
	sr1 = csa->priv1.mfc_sr1_RW | MFC_STATE1_MASTER_RUN_CONTROL_MASK;
	csa->priv1.mfc_sr1_RW = sr1;
	spin_unlock(&csa->register_lock);
}