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
struct func_info {int insn_index; int /*<<< orphan*/  insn_buf; } ;
struct dst_insn {int /*<<< orphan*/ * code; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_insn_insert_tail (struct func_info* const,struct dst_insn*) ; 
 struct dst_insn* dst_new (struct func_info* const,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dst_insn_append(struct func_info * const fp)
{
	int insns_size = (sizeof(unsigned int) * fp->insn_index);
	struct dst_insn *dp;

	dp = dst_new(fp, fp->insn_index, NULL, insns_size);
	if (insns_size)
		memcpy(&dp->code[0], fp->insn_buf, insns_size);
	dst_insn_insert_tail(fp, dp);

	fp->insn_index = 0;
}