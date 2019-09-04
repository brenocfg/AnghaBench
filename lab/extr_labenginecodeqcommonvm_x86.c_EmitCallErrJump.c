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
typedef  int /*<<< orphan*/  vm_t ;

/* Variables and functions */
 int /*<<< orphan*/  Emit4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EmitCallRel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EmitString (char*) ; 
 int /*<<< orphan*/  VM_JMP_VIOLATION ; 

__attribute__((used)) static void EmitCallErrJump(vm_t *vm, int sysCallOfs)
{
	EmitString("B8");			// mov eax, 0x12345678
	Emit4(VM_JMP_VIOLATION);

	EmitCallRel(vm, sysCallOfs);
}