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
typedef  int u_int32_t ;
struct aac_softc {int /*<<< orphan*/  aac_aifq_lock; struct aac_fib_context* fibctx; } ;
struct aac_fib_context {int unique; struct aac_fib_context* next; struct aac_fib_context* prev; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENOMEM ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  M_AACBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  aac_close_aif (struct aac_softc*,scalar_t__) ; 
 int copyout (int*,void*,int) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 struct aac_fib_context* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
aac_open_aif(struct aac_softc *sc, caddr_t arg)
{
	struct aac_fib_context *fibctx, *ctx;
	int error = 0;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	fibctx = malloc(sizeof(struct aac_fib_context), M_AACBUF, M_NOWAIT|M_ZERO);
	if (fibctx == NULL)
		return (ENOMEM);

	mtx_lock(&sc->aac_aifq_lock);
	/* all elements are already 0, add to queue */
	if (sc->fibctx == NULL)
		sc->fibctx = fibctx;
	else {
		for (ctx = sc->fibctx; ctx->next; ctx = ctx->next)
			;
		ctx->next = fibctx;
		fibctx->prev = ctx;
	}

	/* evaluate unique value */
	fibctx->unique = (*(u_int32_t *)&fibctx & 0xffffffff);
	ctx = sc->fibctx;
	while (ctx != fibctx) {
		if (ctx->unique == fibctx->unique) {
			fibctx->unique++;
			ctx = sc->fibctx;
		} else {
			ctx = ctx->next;
		}
	}
	mtx_unlock(&sc->aac_aifq_lock);

	error = copyout(&fibctx->unique, (void *)arg, sizeof(u_int32_t));
	if (error)
		aac_close_aif(sc, (caddr_t)ctx);
	return error;
}