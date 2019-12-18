#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct TYPE_5__ {void* mc_tls; int /*<<< orphan*/  mc_fpc_eir; int /*<<< orphan*/ * mc_fpregs; int /*<<< orphan*/  mc_fpused; int /*<<< orphan*/  mulhi; int /*<<< orphan*/  mullo; int /*<<< orphan*/  sr; int /*<<< orphan*/ * mc_regs; int /*<<< orphan*/  mc_pc; int /*<<< orphan*/  mc_onstack; } ;
typedef  TYPE_1__ mcontext_t ;
struct TYPE_6__ {scalar_t__ mc_tls; int /*<<< orphan*/  mc_fpc_eir; int /*<<< orphan*/ * mc_fpregs; int /*<<< orphan*/  mc_fpused; int /*<<< orphan*/  mulhi; int /*<<< orphan*/  mullo; int /*<<< orphan*/  sr; int /*<<< orphan*/ * mc_regs; int /*<<< orphan*/  mc_pc; int /*<<< orphan*/  mc_onstack; } ;
typedef  TYPE_2__ mcontext32_t ;

/* Variables and functions */
 int set_mcontext (struct thread*,TYPE_1__*) ; 

__attribute__((used)) static int
set_mcontext32(struct thread *td, mcontext32_t *mcp)
{
	mcontext_t mcp64;
	unsigned i;

	mcp64.mc_onstack = mcp->mc_onstack;
	mcp64.mc_pc = mcp->mc_pc;
	for (i = 0; i < 32; i++)
		mcp64.mc_regs[i] = mcp->mc_regs[i];
	mcp64.sr = mcp->sr;
	mcp64.mullo = mcp->mullo;
	mcp64.mulhi = mcp->mulhi;
	mcp64.mc_fpused = mcp->mc_fpused;
	for (i = 0; i < 33; i++)
		mcp64.mc_fpregs[i] = mcp->mc_fpregs[i];
	mcp64.mc_fpc_eir = mcp->mc_fpc_eir;
	mcp64.mc_tls = (void *)(intptr_t)mcp->mc_tls;

	return (set_mcontext(td, &mcp64));
}