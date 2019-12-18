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

/* Variables and functions */
#define  PISTACHIO_CORE_REV_A1 129 
#define  PISTACHIO_CORE_REV_B0 128 
 scalar_t__ PISTACHIO_CORE_REV_REG ; 
 int __raw_readl (void const*) ; 

const char *get_system_type(void)
{
	u32 core_rev;
	const char *sys_type;

	core_rev = __raw_readl((const void *)PISTACHIO_CORE_REV_REG);

	switch (core_rev) {
	case PISTACHIO_CORE_REV_B0:
		sys_type = "IMG Pistachio SoC (B0)";
		break;

	case PISTACHIO_CORE_REV_A1:
		sys_type = "IMG Pistachio SoC (A1)";
		break;

	default:
		sys_type = "IMG Pistachio SoC";
		break;
	}

	return sys_type;
}