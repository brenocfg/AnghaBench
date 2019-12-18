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
struct rv_jit_context {int dummy; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int is_13b_check (int,int) ; 
 int rv_offset (scalar_t__,int,struct rv_jit_context*) ; 

__attribute__((used)) static int rv_offset_check(int *rvoff, s16 off, int insn,
			   struct rv_jit_context *ctx)
{
	*rvoff = rv_offset(insn + off, insn, ctx);
	return is_13b_check(*rvoff, insn);
}