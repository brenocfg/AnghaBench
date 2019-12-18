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
struct vmcs12 {int pin_based_vm_exec_control; } ;

/* Variables and functions */
 int PIN_BASED_VIRTUAL_NMIS ; 

__attribute__((used)) static inline bool nested_cpu_has_virtual_nmis(struct vmcs12 *vmcs12)
{
	return vmcs12->pin_based_vm_exec_control & PIN_BASED_VIRTUAL_NMIS;
}