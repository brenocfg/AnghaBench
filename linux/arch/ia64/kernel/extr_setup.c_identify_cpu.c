#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct cpuinfo_ia64 {int threads_per_core; int cores_per_socket; int num_log; int socket_id; unsigned int number; unsigned int revision; unsigned int model; unsigned int family; unsigned int archrev; long unimpl_va_mask; long unimpl_pa_mask; int /*<<< orphan*/  model_name; int /*<<< orphan*/  features; int /*<<< orphan*/  ppn; int /*<<< orphan*/  cpu; int /*<<< orphan*/  vendor; } ;
struct TYPE_7__ {unsigned long impl_va_msb; } ;
struct TYPE_9__ {TYPE_1__ pal_vm_info_2_s; } ;
typedef  TYPE_3__ pal_vm_info_2_u_t ;
struct TYPE_8__ {unsigned long phys_add_size; } ;
struct TYPE_10__ {TYPE_2__ pal_vm_info_1_s; } ;
typedef  TYPE_4__ pal_vm_info_1_u_t ;
typedef  scalar_t__ pal_status_t ;

/* Variables and functions */
 scalar_t__ PAL_STATUS_SUCCESS ; 
 int /*<<< orphan*/  get_model_name (unsigned int,unsigned int) ; 
 unsigned long ia64_get_cpuid (int) ; 
 scalar_t__ ia64_pal_vm_summary (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  identify_siblings (struct cpuinfo_ia64*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int smp_num_siblings ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void
identify_cpu (struct cpuinfo_ia64 *c)
{
	union {
		unsigned long bits[5];
		struct {
			/* id 0 & 1: */
			char vendor[16];

			/* id 2 */
			u64 ppn;		/* processor serial number */

			/* id 3: */
			unsigned number		:  8;
			unsigned revision	:  8;
			unsigned model		:  8;
			unsigned family		:  8;
			unsigned archrev	:  8;
			unsigned reserved	: 24;

			/* id 4: */
			u64 features;
		} field;
	} cpuid;
	pal_vm_info_1_u_t vm1;
	pal_vm_info_2_u_t vm2;
	pal_status_t status;
	unsigned long impl_va_msb = 50, phys_addr_size = 44;	/* Itanium defaults */
	int i;
	for (i = 0; i < 5; ++i)
		cpuid.bits[i] = ia64_get_cpuid(i);

	memcpy(c->vendor, cpuid.field.vendor, 16);
#ifdef CONFIG_SMP
	c->cpu = smp_processor_id();

	/* below default values will be overwritten  by identify_siblings() 
	 * for Multi-Threading/Multi-Core capable CPUs
	 */
	c->threads_per_core = c->cores_per_socket = c->num_log = 1;
	c->socket_id = -1;

	identify_siblings(c);

	if (c->threads_per_core > smp_num_siblings)
		smp_num_siblings = c->threads_per_core;
#endif
	c->ppn = cpuid.field.ppn;
	c->number = cpuid.field.number;
	c->revision = cpuid.field.revision;
	c->model = cpuid.field.model;
	c->family = cpuid.field.family;
	c->archrev = cpuid.field.archrev;
	c->features = cpuid.field.features;
	c->model_name = get_model_name(c->family, c->model);

	status = ia64_pal_vm_summary(&vm1, &vm2);
	if (status == PAL_STATUS_SUCCESS) {
		impl_va_msb = vm2.pal_vm_info_2_s.impl_va_msb;
		phys_addr_size = vm1.pal_vm_info_1_s.phys_add_size;
	}
	c->unimpl_va_mask = ~((7L<<61) | ((1L << (impl_va_msb + 1)) - 1));
	c->unimpl_pa_mask = ~((1L<<63) | ((1L << phys_addr_size) - 1));
}