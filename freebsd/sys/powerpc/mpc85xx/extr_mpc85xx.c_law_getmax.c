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
 int /*<<< orphan*/  SPR_SVR ; 
#define  SVR_MPC8533 139 
#define  SVR_MPC8533E 138 
#define  SVR_MPC8548 137 
#define  SVR_MPC8548E 136 
#define  SVR_MPC8555 135 
#define  SVR_MPC8555E 134 
#define  SVR_P5020 133 
#define  SVR_P5020E 132 
#define  SVR_P5021 131 
#define  SVR_P5021E 130 
#define  SVR_P5040 129 
#define  SVR_P5040E 128 
 int SVR_VER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 

int
law_getmax(void)
{
	uint32_t ver;
	int law_max;

	ver = SVR_VER(mfspr(SPR_SVR));
	switch (ver) {
	case SVR_MPC8555:
	case SVR_MPC8555E:
		law_max = 8;
		break;
	case SVR_MPC8533:
	case SVR_MPC8533E:
	case SVR_MPC8548:
	case SVR_MPC8548E:
		law_max = 10;
		break;
	case SVR_P5020:
	case SVR_P5020E:
	case SVR_P5021:
	case SVR_P5021E:
	case SVR_P5040:
	case SVR_P5040E:
		law_max = 32;
		break;
	default:
		law_max = 8;
	}

	return (law_max);
}