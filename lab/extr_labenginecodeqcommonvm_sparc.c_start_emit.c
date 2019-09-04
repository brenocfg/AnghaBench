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
struct func_info {int saved_icount; scalar_t__ force_emit; scalar_t__ insn_index; } ;

/* Variables and functions */

__attribute__((used)) static void start_emit(struct func_info * const fp, int i_count)
{
	fp->saved_icount = i_count;
	fp->insn_index = 0;
	fp->force_emit = 0;
}