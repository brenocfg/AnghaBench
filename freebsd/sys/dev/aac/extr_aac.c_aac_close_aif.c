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
typedef  scalar_t__ uint32_t ;
struct aac_softc {int /*<<< orphan*/  aac_aifq_lock; struct aac_fib_context* fibctx; } ;
struct aac_fib_context {scalar_t__ unique; TYPE_1__* prev; struct aac_fib_context* next; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {struct aac_fib_context* next; } ;

/* Variables and functions */
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  M_AACBUF ; 
 int /*<<< orphan*/  free (struct aac_fib_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
aac_close_aif(struct aac_softc *sc, caddr_t arg)
{
	struct aac_fib_context *ctx;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	mtx_lock(&sc->aac_aifq_lock);
	for (ctx = sc->fibctx; ctx; ctx = ctx->next) {
		if (ctx->unique == *(uint32_t *)&arg) {
			if (ctx == sc->fibctx)
				sc->fibctx = NULL;
			else {
				ctx->prev->next = ctx->next;
				if (ctx->next)
					ctx->next->prev = ctx->prev;
			}
			break;
		}
	}
	mtx_unlock(&sc->aac_aifq_lock);
	if (ctx)
		free(ctx, M_AACBUF);

	return 0;
}