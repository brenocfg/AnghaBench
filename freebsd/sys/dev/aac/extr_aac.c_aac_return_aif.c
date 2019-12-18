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
struct aac_softc {int aifq_idx; int /*<<< orphan*/  aac_aifq_lock; int /*<<< orphan*/  aac_dev; int /*<<< orphan*/ * aac_aifq; } ;
struct aac_fib_context {int ctx_idx; scalar_t__ ctx_wrap; } ;
struct aac_fib {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int AAC_AIFQ_LENGTH ; 
 int EAGAIN ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int copyout (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
aac_return_aif(struct aac_softc *sc, struct aac_fib_context *ctx, caddr_t uptr)
{
	int current, error;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	mtx_lock(&sc->aac_aifq_lock);
	current = ctx->ctx_idx;
	if (current == sc->aifq_idx && !ctx->ctx_wrap) {
		/* empty */
		mtx_unlock(&sc->aac_aifq_lock);
		return (EAGAIN);
	}
	error =
		copyout(&sc->aac_aifq[current], (void *)uptr, sizeof(struct aac_fib));
	if (error)
		device_printf(sc->aac_dev,
		    "aac_return_aif: copyout returned %d\n", error);
	else {
		ctx->ctx_wrap = 0;
		ctx->ctx_idx = (current + 1) % AAC_AIFQ_LENGTH;
	}
	mtx_unlock(&sc->aac_aifq_lock);
	return(error);
}