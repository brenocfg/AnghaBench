#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int vm_quantum_mask; } ;
typedef  TYPE_1__ vmem_t ;
typedef  int vmem_size_t ;

/* Variables and functions */

vmem_size_t
vmem_roundup_size(vmem_t *vm, vmem_size_t size)
{

	return (size + vm->vm_quantum_mask) & ~vm->vm_quantum_mask;
}