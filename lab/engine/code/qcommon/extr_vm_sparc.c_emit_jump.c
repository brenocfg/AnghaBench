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
typedef  int /*<<< orphan*/  vm_t ;
struct func_info {int dummy; } ;
typedef  enum sparc_iname { ____Placeholder_sparc_iname } sparc_iname ;

/* Variables and functions */
 int /*<<< orphan*/  end_emit (struct func_info* const) ; 
 int /*<<< orphan*/  jump_insn_append (int /*<<< orphan*/ *,struct func_info* const,int,int) ; 

__attribute__((used)) static void emit_jump(vm_t *vm, struct func_info * const fp, enum sparc_iname iname, int dest)
{
	end_emit(fp);
	jump_insn_append(vm, fp, iname, dest);
}