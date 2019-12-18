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
typedef  int /*<<< orphan*/  db_addr_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_TYPE_BREAKPOINT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dbg_capable () ; 
 unsigned int dbg_find_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
kdb_cpu_pc_is_singlestep(db_addr_t pc)
{
	/*
	 * XXX: If the platform fails to enable its debug arch.
	 *      there will be no stepping capabilities
	 *      (SOFTWARE_SSTEP is not defined for __ARM_ARCH >= 6).
	 */
	if (!dbg_capable())
		return (FALSE);

	if (dbg_find_slot(DBG_TYPE_BREAKPOINT, pc) != ~0U)
		return (TRUE);

	return (FALSE);
}