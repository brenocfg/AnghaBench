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
typedef  int vmem_addr_t ;
struct sgx_softc {int epc_base; struct epc_page* epc_pages; int /*<<< orphan*/  vmem_epc; } ;
struct epc_page {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int M_FIRSTFIT ; 
 int M_NOWAIT ; 
 int PAGE_SIZE ; 
 scalar_t__ vmem_alloc (int /*<<< orphan*/ ,int,int,int*) ; 

__attribute__((used)) static int
sgx_get_epc_page(struct sgx_softc *sc, struct epc_page **epc)
{
	vmem_addr_t addr;
	int i;

	if (vmem_alloc(sc->vmem_epc, PAGE_SIZE, M_FIRSTFIT | M_NOWAIT,
	    &addr) == 0) {
		i = (addr - sc->epc_base) / PAGE_SIZE;
		*epc = &sc->epc_pages[i];
		return (0);
	}

	return (ENOMEM);
}