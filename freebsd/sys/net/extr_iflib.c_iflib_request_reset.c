#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* if_ctx_t ;
struct TYPE_5__ {int /*<<< orphan*/  ifc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFC_DO_RESET ; 
 int /*<<< orphan*/  STATE_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  STATE_UNLOCK (TYPE_1__*) ; 

void
iflib_request_reset(if_ctx_t ctx)
{

	STATE_LOCK(ctx);
	ctx->ifc_flags |= IFC_DO_RESET;
	STATE_UNLOCK(ctx);
}