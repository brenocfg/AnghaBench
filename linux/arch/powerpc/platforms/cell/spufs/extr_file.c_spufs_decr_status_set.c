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
typedef  scalar_t__ u64 ;
struct TYPE_3__ {int /*<<< orphan*/  mfc_control_RW; } ;
struct TYPE_4__ {TYPE_1__ priv2; } ;
struct spu_context {TYPE_2__ csa; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFC_CNTL_DECREMENTER_RUNNING ; 
 int spu_acquire_saved (struct spu_context*) ; 
 int /*<<< orphan*/  spu_release_saved (struct spu_context*) ; 

__attribute__((used)) static int spufs_decr_status_set(void *data, u64 val)
{
	struct spu_context *ctx = data;
	int ret;

	ret = spu_acquire_saved(ctx);
	if (ret)
		return ret;
	if (val)
		ctx->csa.priv2.mfc_control_RW |= MFC_CNTL_DECREMENTER_RUNNING;
	else
		ctx->csa.priv2.mfc_control_RW &= ~MFC_CNTL_DECREMENTER_RUNNING;
	spu_release_saved(ctx);

	return 0;
}