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

/* Variables and functions */
 int /*<<< orphan*/  __put_user_asm (unsigned int,unsigned int*,int,char*) ; 

__attribute__((used)) static int __patch_instruction(unsigned int *exec_addr, unsigned int instr,
			       unsigned int *patch_addr)
{
	int err = 0;

	__put_user_asm(instr, patch_addr, err, "stw");
	if (err)
		return err;

	asm ("dcbst 0, %0; sync; icbi 0,%1; sync; isync" :: "r" (patch_addr),
							    "r" (exec_addr));

	return 0;
}