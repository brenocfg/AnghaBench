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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_32BIT ; 
 int /*<<< orphan*/  CONFIG_64BIT ; 
 int /*<<< orphan*/  CONFIG_MIPS32_O32 ; 
 int /*<<< orphan*/  CONFIG_MIPS_O32_FP64_SUPPORT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIF_32BIT_FPREGS ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cop1_64bit(struct pt_regs *xcp)
{
	if (IS_ENABLED(CONFIG_64BIT) && !IS_ENABLED(CONFIG_MIPS32_O32))
		return 1;
	else if (IS_ENABLED(CONFIG_32BIT) &&
		 !IS_ENABLED(CONFIG_MIPS_O32_FP64_SUPPORT))
		return 0;

	return !test_thread_flag(TIF_32BIT_FPREGS);
}