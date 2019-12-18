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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CPU_LOONGSON3_WORKAROUNDS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UASM_i_LL (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  UASM_i_LW (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ cpu_has_64bits ; 
 int /*<<< orphan*/  uasm_i_ld (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_lld (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_sync (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iPTE_LW(u32 **p, unsigned int pte, unsigned int ptr)
{
#ifdef CONFIG_SMP
	if (IS_ENABLED(CONFIG_CPU_LOONGSON3_WORKAROUNDS))
		uasm_i_sync(p, 0);
# ifdef CONFIG_PHYS_ADDR_T_64BIT
	if (cpu_has_64bits)
		uasm_i_lld(p, pte, 0, ptr);
	else
# endif
		UASM_i_LL(p, pte, 0, ptr);
#else
# ifdef CONFIG_PHYS_ADDR_T_64BIT
	if (cpu_has_64bits)
		uasm_i_ld(p, pte, 0, ptr);
	else
# endif
		UASM_i_LW(p, pte, 0, ptr);
#endif
}