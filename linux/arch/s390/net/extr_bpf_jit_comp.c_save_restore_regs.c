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
typedef  int /*<<< orphan*/  u32 ;
struct bpf_jit {int dummy; } ;

/* Variables and functions */
 int REGS_SAVE ; 
 int get_end (struct bpf_jit*,int) ; 
 int get_start (struct bpf_jit*,int) ; 
 int /*<<< orphan*/  restore_regs (struct bpf_jit*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_regs (struct bpf_jit*,int,int) ; 

__attribute__((used)) static void save_restore_regs(struct bpf_jit *jit, int op, u32 stack_depth)
{

	int re = 6, rs;

	do {
		rs = get_start(jit, re);
		if (!rs)
			break;
		re = get_end(jit, rs + 1);
		if (op == REGS_SAVE)
			save_regs(jit, rs, re);
		else
			restore_regs(jit, rs, re, stack_depth);
		re++;
	} while (re <= 15);
}