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
struct TYPE_2__ {int mode; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int SYSMODE_PREFIX_DATA ; 
 int /*<<< orphan*/  common_bitsearch16 (struct x86emu*,int) ; 
 int /*<<< orphan*/  common_bitsearch32 (struct x86emu*,int) ; 

__attribute__((used)) static void
common_bitsearch(struct x86emu *emu, int diff)
{
	if (emu->x86.mode & SYSMODE_PREFIX_DATA)
		common_bitsearch32(emu, diff);
	else
		common_bitsearch16(emu, diff);
}