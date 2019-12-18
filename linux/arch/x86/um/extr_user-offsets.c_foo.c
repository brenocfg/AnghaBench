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
typedef  int /*<<< orphan*/  syscalls ;
struct user_regs_struct {int dummy; } ;
struct user_fpxregs_struct {int dummy; } ;
struct user_fpregs_struct {int dummy; } ;
struct _fpstate {int dummy; } ;

/* Variables and functions */
 int CS ; 
 int /*<<< orphan*/  DEFINE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DEFINE_LONGS (int /*<<< orphan*/ ,int) ; 
 int DS ; 
 int EAX ; 
 int EBP ; 
 int EBX ; 
 int ECX ; 
 int EDI ; 
 int EDX ; 
 int EFL ; 
 int EFLAGS ; 
 int EIP ; 
 int ES ; 
 int ESI ; 
 int FS ; 
 int GS ; 
 int /*<<< orphan*/  HOST_AX ; 
 int /*<<< orphan*/  HOST_BP ; 
 int /*<<< orphan*/  HOST_BX ; 
 int /*<<< orphan*/  HOST_CS ; 
 int /*<<< orphan*/  HOST_CX ; 
 int /*<<< orphan*/  HOST_DI ; 
 int /*<<< orphan*/  HOST_DS ; 
 int /*<<< orphan*/  HOST_DX ; 
 int /*<<< orphan*/  HOST_EFLAGS ; 
 int /*<<< orphan*/  HOST_ES ; 
 int /*<<< orphan*/  HOST_FPX_SIZE ; 
 int /*<<< orphan*/  HOST_FP_SIZE ; 
 int /*<<< orphan*/  HOST_FS ; 
 int /*<<< orphan*/  HOST_GS ; 
 int /*<<< orphan*/  HOST_IP ; 
 int /*<<< orphan*/  HOST_ORIG_AX ; 
 int /*<<< orphan*/  HOST_R10 ; 
 int /*<<< orphan*/  HOST_R11 ; 
 int /*<<< orphan*/  HOST_R12 ; 
 int /*<<< orphan*/  HOST_R13 ; 
 int /*<<< orphan*/  HOST_R14 ; 
 int /*<<< orphan*/  HOST_R15 ; 
 int /*<<< orphan*/  HOST_R8 ; 
 int /*<<< orphan*/  HOST_R9 ; 
 int /*<<< orphan*/  HOST_SI ; 
 int /*<<< orphan*/  HOST_SP ; 
 int /*<<< orphan*/  HOST_SS ; 
 int /*<<< orphan*/  NR_syscalls ; 
 int ORIG_EAX ; 
 int ORIG_RAX ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLPRI ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int R10 ; 
 int R11 ; 
 int R12 ; 
 int R13 ; 
 int R14 ; 
 int R15 ; 
 int R8 ; 
 int R9 ; 
 int RAX ; 
 int RBP ; 
 int RBX ; 
 int RCX ; 
 int RDI ; 
 int RDX ; 
 int RIP ; 
 int RSI ; 
 int RSP ; 
 int SS ; 
 int UESP ; 
 int /*<<< orphan*/  UM_FRAME_SIZE ; 
 int /*<<< orphan*/  UM_POLLIN ; 
 int /*<<< orphan*/  UM_POLLOUT ; 
 int /*<<< orphan*/  UM_POLLPRI ; 
 int /*<<< orphan*/  UM_PROT_EXEC ; 
 int /*<<< orphan*/  UM_PROT_READ ; 
 int /*<<< orphan*/  UM_PROT_WRITE ; 
 int /*<<< orphan*/  __NR_syscall_max ; 

void foo(void)
{
#ifdef __i386__
	DEFINE_LONGS(HOST_FP_SIZE, sizeof(struct user_fpregs_struct));
	DEFINE_LONGS(HOST_FPX_SIZE, sizeof(struct user_fpxregs_struct));

	DEFINE(HOST_IP, EIP);
	DEFINE(HOST_SP, UESP);
	DEFINE(HOST_EFLAGS, EFL);
	DEFINE(HOST_AX, EAX);
	DEFINE(HOST_BX, EBX);
	DEFINE(HOST_CX, ECX);
	DEFINE(HOST_DX, EDX);
	DEFINE(HOST_SI, ESI);
	DEFINE(HOST_DI, EDI);
	DEFINE(HOST_BP, EBP);
	DEFINE(HOST_CS, CS);
	DEFINE(HOST_SS, SS);
	DEFINE(HOST_DS, DS);
	DEFINE(HOST_FS, FS);
	DEFINE(HOST_ES, ES);
	DEFINE(HOST_GS, GS);
	DEFINE(HOST_ORIG_AX, ORIG_EAX);
#else
#ifdef FP_XSTATE_MAGIC1
	DEFINE_LONGS(HOST_FP_SIZE, 2696);
#else
	DEFINE(HOST_FP_SIZE, sizeof(struct _fpstate) / sizeof(unsigned long));
#endif
	DEFINE_LONGS(HOST_BX, RBX);
	DEFINE_LONGS(HOST_CX, RCX);
	DEFINE_LONGS(HOST_DI, RDI);
	DEFINE_LONGS(HOST_SI, RSI);
	DEFINE_LONGS(HOST_DX, RDX);
	DEFINE_LONGS(HOST_BP, RBP);
	DEFINE_LONGS(HOST_AX, RAX);
	DEFINE_LONGS(HOST_R8, R8);
	DEFINE_LONGS(HOST_R9, R9);
	DEFINE_LONGS(HOST_R10, R10);
	DEFINE_LONGS(HOST_R11, R11);
	DEFINE_LONGS(HOST_R12, R12);
	DEFINE_LONGS(HOST_R13, R13);
	DEFINE_LONGS(HOST_R14, R14);
	DEFINE_LONGS(HOST_R15, R15);
	DEFINE_LONGS(HOST_ORIG_AX, ORIG_RAX);
	DEFINE_LONGS(HOST_CS, CS);
	DEFINE_LONGS(HOST_SS, SS);
	DEFINE_LONGS(HOST_EFLAGS, EFLAGS);
#if 0
	DEFINE_LONGS(HOST_FS, FS);
	DEFINE_LONGS(HOST_GS, GS);
	DEFINE_LONGS(HOST_DS, DS);
	DEFINE_LONGS(HOST_ES, ES);
#endif

	DEFINE_LONGS(HOST_IP, RIP);
	DEFINE_LONGS(HOST_SP, RSP);
#endif

	DEFINE(UM_FRAME_SIZE, sizeof(struct user_regs_struct));
	DEFINE(UM_POLLIN, POLLIN);
	DEFINE(UM_POLLPRI, POLLPRI);
	DEFINE(UM_POLLOUT, POLLOUT);

	DEFINE(UM_PROT_READ, PROT_READ);
	DEFINE(UM_PROT_WRITE, PROT_WRITE);
	DEFINE(UM_PROT_EXEC, PROT_EXEC);

	DEFINE(__NR_syscall_max, sizeof(syscalls) - 1);
	DEFINE(NR_syscalls, sizeof(syscalls));
}