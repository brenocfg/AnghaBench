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
typedef  int uint16_t ;
struct sgx_softc {int /*<<< orphan*/  mtx_encls; } ;
struct epc_page {scalar_t__ base; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int SGX_EFAULT ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int sgx_eextend (void*,void*) ; 

__attribute__((used)) static int
sgx_measure_page(struct sgx_softc *sc, struct epc_page *secs,
    struct epc_page *epc, uint16_t mrmask)
{
	int i, j;
	int ret;

	mtx_lock(&sc->mtx_encls);

	for (i = 0, j = 1; i < PAGE_SIZE; i += 0x100, j <<= 1) {
		if (!(j & mrmask))
			continue;

		ret = sgx_eextend((void *)secs->base,
		    (void *)(epc->base + i));
		if (ret == SGX_EFAULT) {
			mtx_unlock(&sc->mtx_encls);
			return (ret);
		}
	}

	mtx_unlock(&sc->mtx_encls);

	return (0);
}