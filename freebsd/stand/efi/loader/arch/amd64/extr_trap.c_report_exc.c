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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct trapframe {int tf_trapno; int /*<<< orphan*/  tf_r15; int /*<<< orphan*/  tf_r14; int /*<<< orphan*/  tf_r13; int /*<<< orphan*/  tf_r12; int /*<<< orphan*/  tf_r11; int /*<<< orphan*/  tf_r10; int /*<<< orphan*/  tf_rbp; int /*<<< orphan*/  tf_rbx; int /*<<< orphan*/  tf_rax; int /*<<< orphan*/  tf_r9; int /*<<< orphan*/  tf_r8; int /*<<< orphan*/  tf_rcx; int /*<<< orphan*/  tf_rdx; int /*<<< orphan*/  tf_rsi; int /*<<< orphan*/  tf_rdi; scalar_t__ tf_rflags; scalar_t__ tf_err; int /*<<< orphan*/  tf_rip; int /*<<< orphan*/  tf_rsp; int /*<<< orphan*/  tf_addr; scalar_t__ tf_gs; scalar_t__ tf_fs; scalar_t__ tf_es; scalar_t__ tf_ds; scalar_t__ tf_cs; scalar_t__ tf_ss; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void
report_exc(struct trapframe *tf)
{

	/*
	 * printf() depends on loader runtime and UEFI firmware health
	 * to produce the console output, in case of exception, the
	 * loader or firmware runtime may fail to support the printf().
	 */
	printf("===================================================="
	    "============================\n");
	printf("Exception %u\n", tf->tf_trapno);
	printf("ss 0x%04hx cs 0x%04hx ds 0x%04hx es 0x%04hx fs 0x%04hx "
	    "gs 0x%04hx\n",
	    (uint16_t)tf->tf_ss, (uint16_t)tf->tf_cs, (uint16_t)tf->tf_ds,
	    (uint16_t)tf->tf_es, (uint16_t)tf->tf_fs, (uint16_t)tf->tf_gs);
	printf("err 0x%08x rfl 0x%08x addr 0x%016lx\n"
	    "rsp 0x%016lx rip 0x%016lx\n",
	    (uint32_t)tf->tf_err, (uint32_t)tf->tf_rflags, tf->tf_addr,
	    tf->tf_rsp, tf->tf_rip);
	printf(
	    "rdi 0x%016lx rsi 0x%016lx rdx 0x%016lx\n"
	    "rcx 0x%016lx r8  0x%016lx r9  0x%016lx\n"
	    "rax 0x%016lx rbx 0x%016lx rbp 0x%016lx\n"
	    "r10 0x%016lx r11 0x%016lx r12 0x%016lx\n"
	    "r13 0x%016lx r14 0x%016lx r15 0x%016lx\n",
	    tf->tf_rdi, tf->tf_rsi, tf->tf_rdx, tf->tf_rcx, tf->tf_r8,
	    tf->tf_r9, tf->tf_rax, tf->tf_rbx, tf->tf_rbp, tf->tf_r10,
	    tf->tf_r11, tf->tf_r12, tf->tf_r13, tf->tf_r14, tf->tf_r15);
	printf("Machine stopped.\n");
}