#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct src_insn {struct src_insn* next; } ;
struct func_info {TYPE_1__* first; } ;
struct TYPE_2__ {struct src_insn* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  Z_Free (struct src_insn*) ; 

__attribute__((used)) static void free_source_insns(struct func_info * const fp)
{
	struct src_insn *sp = fp->first->next;

	while (sp) {
		struct src_insn *next = sp->next;
		Z_Free(sp);
		sp = next;
	}
}