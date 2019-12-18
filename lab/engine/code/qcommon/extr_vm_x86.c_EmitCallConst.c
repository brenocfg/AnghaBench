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
 int /*<<< orphan*/  Emit4 (int) ; 
 int /*<<< orphan*/  EmitCallIns (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EmitCallRel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EmitString (char*) ; 

void EmitCallConst(vm_t *vm, int cdest, int callProcOfsSyscall)
{
	if(cdest < 0)
	{
		EmitString("B8");	// mov eax, cdest
		Emit4(cdest);

		EmitCallRel(vm, callProcOfsSyscall);
	}
	else
		EmitCallIns(vm, cdest);
}