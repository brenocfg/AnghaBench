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
struct vmspace {int dummy; } ;
struct vm {struct vmspace* vmspace; } ;

/* Variables and functions */

struct vmspace *
vm_get_vmspace(struct vm *vm)
{

	return (vm->vmspace);
}