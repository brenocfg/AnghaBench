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

/* Variables and functions */
 int /*<<< orphan*/  is_21b_int (int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 

__attribute__((used)) static int is_21b_check(int off, int insn)
{
	if (!is_21b_int(off)) {
		pr_err("bpf-jit: insn=%d offset=%d not supported yet!\n",
		       insn, (int)off);
		return -1;
	}
	return 0;
}