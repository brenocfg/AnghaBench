#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  ua ;
struct thread {scalar_t__* td_retval; } ;
struct arm_sync_icache_args {scalar_t__ len; scalar_t__ addr; } ;
struct TYPE_4__ {void* ksi_addr; int /*<<< orphan*/  ksi_code; void* ksi_signo; } ;
typedef  TYPE_1__ ksiginfo_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SEGV_ACCERR ; 
 int /*<<< orphan*/  SEGV_MAPERR ; 
 void* SIGSEGV ; 
 scalar_t__ VM_MAXUSER_ADDRESS ; 
 int copyin (void*,struct arm_sync_icache_args*,int) ; 
 int /*<<< orphan*/  cpu_icache_sync_range (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ksiginfo_init_trap (TYPE_1__*) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 int sync_icache (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trapsignal (struct thread*,TYPE_1__*) ; 

__attribute__((used)) static int
arm32_sync_icache(struct thread *td, void *args)
{
	struct arm_sync_icache_args ua;
	int error;
	ksiginfo_t ksi;
#if __ARM_ARCH >= 6
	vm_offset_t rv;
#endif

	if ((error = copyin(args, &ua, sizeof(ua))) != 0)
		return (error);

	if  (ua.len == 0) {
		td->td_retval[0] = 0;
		return (0);
	}

	/*
	 * Validate arguments. Address and length are unsigned,
	 * so we can use wrapped overflow check.
	 */
	if (((ua.addr + ua.len) < ua.addr) ||
	    ((ua.addr + ua.len) > VM_MAXUSER_ADDRESS)) {
		ksiginfo_init_trap(&ksi);
		ksi.ksi_signo = SIGSEGV;
		ksi.ksi_code = SEGV_ACCERR;
		ksi.ksi_addr = (void *)max(ua.addr, VM_MAXUSER_ADDRESS);
		trapsignal(td, &ksi);
		return (EINVAL);
	}

#if __ARM_ARCH >= 6
	rv = sync_icache(ua.addr, ua.len);
	if (rv != 1) {
		ksiginfo_init_trap(&ksi);
		ksi.ksi_signo = SIGSEGV;
		ksi.ksi_code = SEGV_MAPERR;
		ksi.ksi_addr = (void *)rv;
		trapsignal(td, &ksi);
		return (EINVAL);
	}
#else
	cpu_icache_sync_range(ua.addr, ua.len);
#endif

	td->td_retval[0] = 0;
	return (0);
}