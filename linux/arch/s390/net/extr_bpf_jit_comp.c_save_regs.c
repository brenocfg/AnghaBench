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
typedef  int u32 ;
struct bpf_jit {int dummy; } ;

/* Variables and functions */
 int STK_OFF_R6 ; 
 int /*<<< orphan*/  _EMIT6 (int,int) ; 
 int /*<<< orphan*/  _EMIT6_DISP (int,int,int) ; 

__attribute__((used)) static void save_regs(struct bpf_jit *jit, u32 rs, u32 re)
{
	u32 off = STK_OFF_R6 + (rs - 6) * 8;

	if (rs == re)
		/* stg %rs,off(%r15) */
		_EMIT6(0xe300f000 | rs << 20 | off, 0x0024);
	else
		/* stmg %rs,%re,off(%r15) */
		_EMIT6_DISP(0xeb00f000 | rs << 20 | re << 16, 0x0024, off);
}