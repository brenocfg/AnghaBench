#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_4__ {scalar_t__ md_tls_tcb_offset; } ;
struct thread {TYPE_2__ td_md; TYPE_1__* td_frame; } ;
struct image_params {int dummy; } ;
struct TYPE_3__ {int sp; int /*<<< orphan*/  sr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPS_SR_UX ; 
 scalar_t__ TLS_TCB_SIZE32 ; 
 scalar_t__ TLS_TP_OFFSET ; 
 int /*<<< orphan*/  exec_setregs (struct thread*,struct image_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
freebsd32_exec_setregs(struct thread *td, struct image_params *imgp, u_long stack)
{
	exec_setregs(td, imgp, stack);

	/*
	 * See comment in exec_setregs about running 32-bit binaries with 64-bit
	 * registers.
	 */
	td->td_frame->sp -= 65536;

	/*
	 * Clear extended address space bit for userland.
	 */
	td->td_frame->sr &= ~MIPS_SR_UX;

	td->td_md.md_tls_tcb_offset = TLS_TP_OFFSET + TLS_TCB_SIZE32;
}