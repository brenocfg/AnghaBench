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
typedef  int uint32_t ;

/* Variables and functions */
 int DBGSCR_MDBG_EN ; 
 int ENXIO ; 
#define  ID_DFR0_CP_DEBUG_M_V6 131 
#define  ID_DFR0_CP_DEBUG_M_V6_1 130 
#define  ID_DFR0_CP_DEBUG_M_V7 129 
#define  ID_DFR0_CP_DEBUG_M_V7_1 128 
 int /*<<< orphan*/  cp14_dbgdscr_v6_set (int) ; 
 int /*<<< orphan*/  cp14_dbgdscr_v7_set (int) ; 
 int cp14_dbgdscrint_get () ; 
 int dbg_model ; 
 scalar_t__ dbg_monitor_is_enabled () ; 
 int /*<<< orphan*/  isb () ; 

__attribute__((used)) static int
dbg_enable_monitor(void)
{
	uint32_t dbg_dscr;

	/* Already enabled? Just return */
	if (dbg_monitor_is_enabled())
		return (0);

	dbg_dscr = cp14_dbgdscrint_get();

	switch (dbg_model) {
	case ID_DFR0_CP_DEBUG_M_V6:
	case ID_DFR0_CP_DEBUG_M_V6_1: /* fall through */
		cp14_dbgdscr_v6_set(dbg_dscr | DBGSCR_MDBG_EN);
		break;
	case ID_DFR0_CP_DEBUG_M_V7: /* fall through */
	case ID_DFR0_CP_DEBUG_M_V7_1:
		cp14_dbgdscr_v7_set(dbg_dscr | DBGSCR_MDBG_EN);
		break;
	default:
		break;
	}
	isb();

	/* Verify that Monitor mode is set */
	if (dbg_monitor_is_enabled())
		return (0);

	return (ENXIO);
}