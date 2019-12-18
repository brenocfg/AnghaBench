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
struct sgx_softc {int /*<<< orphan*/  epc_pages; scalar_t__ epc_size; scalar_t__ epc_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SGX ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_phys_fictitious_unreg_range (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
sgx_put_epc_area(struct sgx_softc *sc)
{

	vm_phys_fictitious_unreg_range(sc->epc_base,
	    sc->epc_base + sc->epc_size);

	free(sc->epc_pages, M_SGX);
}