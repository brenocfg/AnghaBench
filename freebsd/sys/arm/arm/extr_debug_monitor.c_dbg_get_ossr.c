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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int DBGOSLSR_OSLM0 ; 
 int /*<<< orphan*/  FALSE ; 
#define  ID_DFR0_CP_DEBUG_M_V7 129 
#define  ID_DFR0_CP_DEBUG_M_V7_1 128 
 int /*<<< orphan*/  TRUE ; 
 int cp14_dbgoslsr_get () ; 
 int dbg_model ; 

__attribute__((used)) static __inline boolean_t
dbg_get_ossr(void)
{

	switch (dbg_model) {
	case ID_DFR0_CP_DEBUG_M_V7:
		if ((cp14_dbgoslsr_get() & DBGOSLSR_OSLM0) != 0)
			return (TRUE);

		return (FALSE);
	case ID_DFR0_CP_DEBUG_M_V7_1:
		return (TRUE);
	default:
		return (FALSE);
	}
}