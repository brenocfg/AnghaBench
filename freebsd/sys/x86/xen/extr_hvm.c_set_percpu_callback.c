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
struct xen_hvm_evtchn_upcall_vector {unsigned int vcpu; int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVMOP_set_evtchn_upcall_vector ; 
 int HYPERVISOR_hvm_op (int /*<<< orphan*/ ,struct xen_hvm_evtchn_upcall_vector*) ; 
 int /*<<< orphan*/  IDT_EVTCHN ; 
 int xen_translate_error (int) ; 

__attribute__((used)) static int
set_percpu_callback(unsigned int vcpu)
{
	struct xen_hvm_evtchn_upcall_vector vec;
	int error;

	vec.vcpu = vcpu;
	vec.vector = IDT_EVTCHN;
	error = HYPERVISOR_hvm_op(HVMOP_set_evtchn_upcall_vector, &vec);

	return (error != 0 ? xen_translate_error(error) : 0);
}