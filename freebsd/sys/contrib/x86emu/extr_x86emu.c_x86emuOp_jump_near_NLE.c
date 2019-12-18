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
struct x86emu {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACCESS_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_OF ; 
 int /*<<< orphan*/  F_SF ; 
 int /*<<< orphan*/  F_ZF ; 
 int /*<<< orphan*/  common_jmp_near (struct x86emu*,int) ; 

__attribute__((used)) static void
x86emuOp_jump_near_NLE(struct x86emu *emu)
{
	int sf, of;

	sf = ACCESS_FLAG(F_SF) != 0;
	of = ACCESS_FLAG(F_OF) != 0;

	common_jmp_near(emu, sf == of && !ACCESS_FLAG(F_ZF));
}