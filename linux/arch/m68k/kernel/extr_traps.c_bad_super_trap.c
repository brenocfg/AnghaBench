#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int vector; int format; int pc; } ;
struct TYPE_4__ {unsigned short ssw; int baddr; int /*<<< orphan*/  daddr; } ;
struct TYPE_5__ {TYPE_1__ fmtb; } ;
struct frame {TYPE_3__ ptregs; TYPE_2__ un; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ CPU_IS_020_OR_030 ; 
 unsigned short DF ; 
 unsigned short DFC ; 
 unsigned short RB ; 
 unsigned short RC ; 
 unsigned short RW ; 
 int VEC_ADDRERR ; 
 int /*<<< orphan*/  console_verbose () ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  die_if_kernel (char*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/ * space_names ; 
 int task_pid_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vec_names ; 

void bad_super_trap (struct frame *fp)
{
	int vector = (fp->ptregs.vector >> 2) & 0xff;

	console_verbose();
	if (vector < ARRAY_SIZE(vec_names))
		pr_err("*** %s ***   FORMAT=%X\n",
			vec_names[vector],
			fp->ptregs.format);
	else
		pr_err("*** Exception %d ***   FORMAT=%X\n",
			vector, fp->ptregs.format);
	if (vector == VEC_ADDRERR && CPU_IS_020_OR_030) {
		unsigned short ssw = fp->un.fmtb.ssw;

		pr_err("SSW=%#06x  ", ssw);

		if (ssw & RC)
			pr_err("Pipe stage C instruction fault at %#010lx\n",
				(fp->ptregs.format) == 0xA ?
				fp->ptregs.pc + 2 : fp->un.fmtb.baddr - 2);
		if (ssw & RB)
			pr_err("Pipe stage B instruction fault at %#010lx\n",
				(fp->ptregs.format) == 0xA ?
				fp->ptregs.pc + 4 : fp->un.fmtb.baddr);
		if (ssw & DF)
			pr_err("Data %s fault at %#010lx in %s (pc=%#lx)\n",
				ssw & RW ? "read" : "write",
				fp->un.fmtb.daddr, space_names[ssw & DFC],
				fp->ptregs.pc);
	}
	pr_err("Current process id is %d\n", task_pid_nr(current));
	die_if_kernel("BAD KERNEL TRAP", &fp->ptregs, 0);
}