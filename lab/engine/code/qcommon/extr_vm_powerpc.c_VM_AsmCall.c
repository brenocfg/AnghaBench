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
struct TYPE_3__ {int programStack; long (* systemCall ) (intptr_t*) ;scalar_t__ dataBase; } ;
typedef  TYPE_1__ vm_t ;
struct tms {scalar_t__ tms_utime; } ;
typedef  scalar_t__ clock_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 long ARRAY_LEN (intptr_t*) ; 
 int MAX_VMSYSCALL_ARGS ; 
 TYPE_1__* currentVM ; 
 long stub1 (intptr_t*) ; 
 long stub2 (intptr_t*) ; 
 scalar_t__ time_outside_vm ; 
 int /*<<< orphan*/  times (struct tms*) ; 

__attribute__((used)) static long int
VM_AsmCall( int callSyscallInvNum, int callProgramStack )
{
	vm_t *savedVM = currentVM;
	long int i, ret;
#ifdef VM_TIMES
	struct tms start_time, stop_time;
	clock_t saved_time = time_outside_vm;
	times( &start_time );
#endif

	// save the stack to allow recursive VM entry
	currentVM->programStack = callProgramStack - 4;

	// we need to convert ints to longs on 64bit powerpcs
	if ( sizeof( intptr_t ) == sizeof( int ) ) {
		intptr_t *argPosition = (intptr_t *)((byte *)currentVM->dataBase + callProgramStack + 4);

		// generated code does not invert syscall number
		argPosition[ 0 ] = -1 - callSyscallInvNum;

		ret = currentVM->systemCall( argPosition );
	} else {
		intptr_t args[MAX_VMSYSCALL_ARGS];

		// generated code does not invert syscall number
		args[0] = -1 - callSyscallInvNum;

		int *argPosition = (int *)((byte *)currentVM->dataBase + callProgramStack + 4);
		for( i = 1; i < ARRAY_LEN(args); i++ )
			args[ i ] = argPosition[ i ];

		ret = currentVM->systemCall( args );
	}

	currentVM = savedVM;

#ifdef VM_TIMES
	times( &stop_time );
	time_outside_vm = saved_time + ( stop_time.tms_utime - start_time.tms_utime );
#endif

	return ret;
}