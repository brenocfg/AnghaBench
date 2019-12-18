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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  ID_DFR0_CP_DEBUG_M_V6 131 
#define  ID_DFR0_CP_DEBUG_M_V6_1 130 
#define  ID_DFR0_CP_DEBUG_M_V7 129 
#define  ID_DFR0_CP_DEBUG_M_V7_1 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cp14_dbgdidr_get () ; 
 int dbg_model ; 

__attribute__((used)) static __inline boolean_t
dbg_arch_supported(void)
{
	uint32_t dbg_didr;

	switch (dbg_model) {
	case ID_DFR0_CP_DEBUG_M_V6:
	case ID_DFR0_CP_DEBUG_M_V6_1:
		dbg_didr = cp14_dbgdidr_get();
		/*
		 * read-all-zeroes is used by QEMU
		 * to indicate that ARMv6 debug support
		 * is not implemented. Real hardware has at
		 * least version bits set
		 */
		if (dbg_didr == 0)
			return (FALSE);
		return (TRUE);
	case ID_DFR0_CP_DEBUG_M_V7:
	case ID_DFR0_CP_DEBUG_M_V7_1:	/* fall through */
		return (TRUE);
	default:
		/* We only support valid v6.x/v7.x modes through CP14 */
		return (FALSE);
	}
}