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

/* Variables and functions */
 int /*<<< orphan*/  INTR_MPSAFE ; 
 int /*<<< orphan*/  SWI_VM ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ swi_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swi_vm ; 
 int /*<<< orphan*/  vm_ih ; 

__attribute__((used)) static void
start_softintr(void *dummy)
{

	if (swi_add(NULL, "vm", swi_vm, NULL, SWI_VM, INTR_MPSAFE, &vm_ih))
		panic("died while creating vm swi ithread");
}