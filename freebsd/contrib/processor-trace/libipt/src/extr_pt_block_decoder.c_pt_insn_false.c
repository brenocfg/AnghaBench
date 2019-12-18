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
struct pt_insn_ext {int dummy; } ;
struct pt_insn {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int pt_insn_false(const struct pt_insn *insn,
			 const struct pt_insn_ext *iext)
{
	(void) insn;
	(void) iext;

	return 0;
}