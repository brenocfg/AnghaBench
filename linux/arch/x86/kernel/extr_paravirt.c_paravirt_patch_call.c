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
struct branch {int opcode; unsigned long delta; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  pr_warn (char*,void*) ; 

__attribute__((used)) static unsigned paravirt_patch_call(void *insn_buff, const void *target,
				    unsigned long addr, unsigned len)
{
	const int call_len = 5;
	struct branch *b = insn_buff;
	unsigned long delta = (unsigned long)target - (addr+call_len);

	if (len < call_len) {
		pr_warn("paravirt: Failed to patch indirect CALL at %ps\n", (void *)addr);
		/* Kernel might not be viable if patching fails, bail out: */
		BUG_ON(1);
	}

	b->opcode = 0xe8; /* call */
	b->delta = delta;
	BUILD_BUG_ON(sizeof(*b) != call_len);

	return call_len;
}