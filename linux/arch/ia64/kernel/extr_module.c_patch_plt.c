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
struct plt_entry {scalar_t__* bundle; } ;
struct module {int dummy; } ;
struct insn {int dummy; } ;
typedef  int int64_t ;

/* Variables and functions */
 scalar_t__ apply_imm60 (struct module*,struct insn*,int) ; 
 scalar_t__ apply_imm64 (struct module*,struct insn*,unsigned long) ; 

__attribute__((used)) static int
patch_plt (struct module *mod, struct plt_entry *plt, long target_ip, unsigned long target_gp)
{
	if (apply_imm64(mod, (struct insn *) (plt->bundle[0] + 2), target_gp)
	    && apply_imm60(mod, (struct insn *) (plt->bundle[1] + 2),
			   (target_ip - (int64_t) plt->bundle[1]) / 16))
		return 1;
	return 0;
}