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
struct vcpu_vmx {int /*<<< orphan*/ * pml_pg; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmx_destroy_pml_buffer(struct vcpu_vmx *vmx)
{
	if (vmx->pml_pg) {
		__free_page(vmx->pml_pg);
		vmx->pml_pg = NULL;
	}
}