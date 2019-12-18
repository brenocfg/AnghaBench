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
typedef  TYPE_2__* if_ctx_t ;
struct TYPE_7__ {TYPE_1__* ifc_sctx; int /*<<< orphan*/  ifc_ifp; } ;
struct TYPE_6__ {int isc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  CTX_UNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  IFDI_VFLR_HANDLE (TYPE_2__*) ; 
 int IFF_DRV_RUNNING ; 
 int IFLIB_ADMIN_ALWAYS_RUN ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_task_fn_iov(void *context)
{
	if_ctx_t ctx = context;

	if (!(if_getdrvflags(ctx->ifc_ifp) & IFF_DRV_RUNNING) &&
	    !(ctx->ifc_sctx->isc_flags & IFLIB_ADMIN_ALWAYS_RUN))
		return;

	CTX_LOCK(ctx);
	IFDI_VFLR_HANDLE(ctx);
	CTX_UNLOCK(ctx);
}