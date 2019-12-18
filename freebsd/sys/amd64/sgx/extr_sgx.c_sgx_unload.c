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
struct sgx_softc {int state; int /*<<< orphan*/  mtx; int /*<<< orphan*/  mtx_encls; int /*<<< orphan*/  vmem_epc; int /*<<< orphan*/  sgx_cdev; int /*<<< orphan*/  enclaves; } ;

/* Variables and functions */
 int EBUSY ; 
 int SGX_STATE_RUNNING ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sgx_put_epc_area (struct sgx_softc*) ; 
 struct sgx_softc sgx_sc ; 
 int /*<<< orphan*/  vmem_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sgx_unload(void)
{
	struct sgx_softc *sc;

	sc = &sgx_sc;

	if ((sc->state & SGX_STATE_RUNNING) == 0)
		return (0);

	mtx_lock(&sc->mtx);
	if (!TAILQ_EMPTY(&sc->enclaves)) {
		mtx_unlock(&sc->mtx);
		return (EBUSY);
	}
	sc->state &= ~SGX_STATE_RUNNING;
	mtx_unlock(&sc->mtx);

	destroy_dev(sc->sgx_cdev);

	vmem_destroy(sc->vmem_epc);
	sgx_put_epc_area(sc);

	mtx_destroy(&sc->mtx_encls);
	mtx_destroy(&sc->mtx);

	return (0);
}