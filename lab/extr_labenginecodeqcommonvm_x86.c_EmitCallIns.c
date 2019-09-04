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
struct TYPE_3__ {scalar_t__* instructionPointers; } ;
typedef  TYPE_1__ vm_t ;

/* Variables and functions */
 int /*<<< orphan*/  Emit4 (scalar_t__) ; 
 int /*<<< orphan*/  EmitString (char*) ; 
 int /*<<< orphan*/  JUSED (int) ; 
 scalar_t__ compiledOfs ; 
 int pass ; 

void EmitCallIns(vm_t *vm, int cdest)
{
	JUSED(cdest);

	EmitString("E8");	// call 0x12345678

	// we only know all the jump addresses in the third pass
	if(pass == 2)
		Emit4(vm->instructionPointers[cdest] - compiledOfs - 4);
	else
		compiledOfs += 4;
}