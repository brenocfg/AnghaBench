#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int /*<<< orphan*/  nip; } ;
struct TYPE_5__ {int /*<<< orphan*/  fpscr; } ;
struct TYPE_6__ {TYPE_1__ fp_state; } ;
struct TYPE_7__ {TYPE_2__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGFPE ; 
 int __parse_fpscr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _exception (int /*<<< orphan*/ ,struct pt_regs*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  flush_fp_to_thread (TYPE_3__*) ; 

__attribute__((used)) static void parse_fpe(struct pt_regs *regs)
{
	int code = 0;

	flush_fp_to_thread(current);

	code = __parse_fpscr(current->thread.fp_state.fpscr);

	_exception(SIGFPE, regs, code, regs->nip);
}