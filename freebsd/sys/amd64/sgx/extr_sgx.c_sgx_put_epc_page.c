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
typedef  scalar_t__ vmem_addr_t ;
struct sgx_softc {int /*<<< orphan*/  vmem_epc; scalar_t__ epc_base; } ;
struct epc_page {int index; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void
sgx_put_epc_page(struct sgx_softc *sc, struct epc_page *epc)
{
	vmem_addr_t addr;

	if (epc == NULL)
		return;

	addr = (epc->index * PAGE_SIZE) + sc->epc_base;
	vmem_free(sc->vmem_epc, addr, PAGE_SIZE);
}