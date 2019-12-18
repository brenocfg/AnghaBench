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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  SREG_DBREAKA ; 
 int /*<<< orphan*/  SREG_DBREAKC ; 
 int /*<<< orphan*/  SREG_IBREAKA ; 
 int XCHAL_NUM_DBREAK ; 
 int XCHAL_NUM_IBREAK ; 
 int /*<<< orphan*/  xtensa_set_sr (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xtensa_wsr(unsigned long v, u8 sr)
{
	/* We don't have indexed wsr and creating instruction dynamically
	 * doesn't seem worth it given how small XCHAL_NUM_IBREAK and
	 * XCHAL_NUM_DBREAK are. Thus the switch. In case build breaks here
	 * the switch below needs to be extended.
	 */
	BUILD_BUG_ON(XCHAL_NUM_IBREAK > 2);
	BUILD_BUG_ON(XCHAL_NUM_DBREAK > 2);

	switch (sr) {
#if XCHAL_NUM_IBREAK > 0
	case SREG_IBREAKA + 0:
		xtensa_set_sr(v, SREG_IBREAKA + 0);
		break;
#endif
#if XCHAL_NUM_IBREAK > 1
	case SREG_IBREAKA + 1:
		xtensa_set_sr(v, SREG_IBREAKA + 1);
		break;
#endif

#if XCHAL_NUM_DBREAK > 0
	case SREG_DBREAKA + 0:
		xtensa_set_sr(v, SREG_DBREAKA + 0);
		break;
	case SREG_DBREAKC + 0:
		xtensa_set_sr(v, SREG_DBREAKC + 0);
		break;
#endif
#if XCHAL_NUM_DBREAK > 1
	case SREG_DBREAKA + 1:
		xtensa_set_sr(v, SREG_DBREAKA + 1);
		break;

	case SREG_DBREAKC + 1:
		xtensa_set_sr(v, SREG_DBREAKC + 1);
		break;
#endif
	}
}