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
struct jump_insn {struct jump_insn* next; } ;
struct func_info {struct jump_insn* jump_last; struct jump_insn* jump_first; } ;

/* Variables and functions */

__attribute__((used)) static void jump_insn_insert_tail(struct func_info * const fp,
				  struct jump_insn *jp)
{
	if (!fp->jump_first) {
		fp->jump_first = fp->jump_last = jp;
	} else {
		fp->jump_last->next = jp;
		fp->jump_last = jp;
	}
}