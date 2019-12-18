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
typedef  scalar_t__ uvm_physseg_t ;
struct vm_page {int dummy; } ;
typedef  int /*<<< orphan*/  paddr_t ;

/* Variables and functions */
 scalar_t__ UVM_PHYSSEG_TYPE_INVALID ; 
 int /*<<< orphan*/  atop (int /*<<< orphan*/ ) ; 
 scalar_t__ uvm_physseg_find (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vm_page* uvm_physseg_get_pg (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vm_page *
uvm_phys_to_vm_page(paddr_t pa)
{
	paddr_t pf = atop(pa);
	paddr_t off;
	uvm_physseg_t psi;

	psi = uvm_physseg_find(pf, &off);
	if (psi != UVM_PHYSSEG_TYPE_INVALID)
		return uvm_physseg_get_pg(psi, off);
	return(NULL);
}