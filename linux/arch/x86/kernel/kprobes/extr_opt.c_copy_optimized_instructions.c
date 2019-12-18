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
typedef  int /*<<< orphan*/  u8 ;
struct insn {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int RELATIVEJUMP_SIZE ; 
 int __copy_instruction (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct insn*) ; 
 scalar_t__ alternatives_text_reserved (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  can_boost (struct insn*,int /*<<< orphan*/ *) ; 
 scalar_t__ ftrace_text_reserved (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ jump_label_text_reserved (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int copy_optimized_instructions(u8 *dest, u8 *src, u8 *real)
{
	struct insn insn;
	int len = 0, ret;

	while (len < RELATIVEJUMP_SIZE) {
		ret = __copy_instruction(dest + len, src + len, real + len, &insn);
		if (!ret || !can_boost(&insn, src + len))
			return -EINVAL;
		len += ret;
	}
	/* Check whether the address range is reserved */
	if (ftrace_text_reserved(src, src + len - 1) ||
	    alternatives_text_reserved(src, src + len - 1) ||
	    jump_label_text_reserved(src, src + len - 1))
		return -EBUSY;

	return len;
}