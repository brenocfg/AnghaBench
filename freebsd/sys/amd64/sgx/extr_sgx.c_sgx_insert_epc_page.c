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
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct sgx_enclave {int /*<<< orphan*/  object; } ;
struct epc_page {int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFF_TO_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sgx_insert_epc_page_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sgx_insert_epc_page(struct sgx_enclave *enclave,
    struct epc_page *epc, uint64_t addr)
{
	vm_pindex_t pidx;
	vm_page_t page;

	VM_OBJECT_ASSERT_WLOCKED(enclave->object);

	pidx = OFF_TO_IDX(addr);
	page = PHYS_TO_VM_PAGE(epc->phys);

	sgx_insert_epc_page_by_index(page, enclave->object, pidx);
}