#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmx {int /*<<< orphan*/ * pir_desc; int /*<<< orphan*/ * apic_page; int /*<<< orphan*/  vm; } ;
struct vlapic_vtx {struct vmx* vmx; int /*<<< orphan*/ * pir_desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  post_intr; int /*<<< orphan*/  enable_x2apic_mode; int /*<<< orphan*/  set_tmr; int /*<<< orphan*/  intr_accepted; int /*<<< orphan*/  pending_intr; int /*<<< orphan*/  set_intr_ready; } ;
struct vlapic {int vcpuid; TYPE_1__ ops; struct LAPIC* apic_page; int /*<<< orphan*/  vm; } ;
struct LAPIC {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_VLAPIC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct vlapic* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ posted_interrupts ; 
 scalar_t__ virtual_interrupt_delivery ; 
 int /*<<< orphan*/  vlapic_init (struct vlapic*) ; 
 int /*<<< orphan*/  vmx_enable_x2apic_mode ; 
 int /*<<< orphan*/  vmx_intr_accepted ; 
 int /*<<< orphan*/  vmx_pending_intr ; 
 int /*<<< orphan*/  vmx_post_intr ; 
 int /*<<< orphan*/  vmx_set_intr_ready ; 
 int /*<<< orphan*/  vmx_set_tmr ; 

__attribute__((used)) static struct vlapic *
vmx_vlapic_init(void *arg, int vcpuid)
{
	struct vmx *vmx;
	struct vlapic *vlapic;
	struct vlapic_vtx *vlapic_vtx;

	vmx = arg;

	vlapic = malloc(sizeof(struct vlapic_vtx), M_VLAPIC, M_WAITOK | M_ZERO);
	vlapic->vm = vmx->vm;
	vlapic->vcpuid = vcpuid;
	vlapic->apic_page = (struct LAPIC *)&vmx->apic_page[vcpuid];

	vlapic_vtx = (struct vlapic_vtx *)vlapic;
	vlapic_vtx->pir_desc = &vmx->pir_desc[vcpuid];
	vlapic_vtx->vmx = vmx;

	if (virtual_interrupt_delivery) {
		vlapic->ops.set_intr_ready = vmx_set_intr_ready;
		vlapic->ops.pending_intr = vmx_pending_intr;
		vlapic->ops.intr_accepted = vmx_intr_accepted;
		vlapic->ops.set_tmr = vmx_set_tmr;
		vlapic->ops.enable_x2apic_mode = vmx_enable_x2apic_mode;
	}

	if (posted_interrupts)
		vlapic->ops.post_intr = vmx_post_intr;

	vlapic_init(vlapic);

	return (vlapic);
}