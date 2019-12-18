#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ ocs_hw_t ;
struct TYPE_7__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* callback ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ ocs_hw_async_call_ctx_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ocs_hw_async_cb(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void *arg)
{
	ocs_hw_async_call_ctx_t *ctx = arg;

	if (ctx != NULL) {
		if (ctx->callback != NULL) {
			(*ctx->callback)(hw, status, mqe, ctx->arg);
		}
		ocs_free(hw->os, ctx, sizeof(*ctx));
	}
}