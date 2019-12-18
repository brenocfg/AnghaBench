#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int cfg; } ;
struct TYPE_7__ {int type; TYPE_1__ opt; } ;
typedef  TYPE_2__ ct_board_t ;

/* Variables and functions */
#define  B_TAU2_E1 135 
#define  B_TAU2_E1D 134 
#define  B_TAU2_G703 133 
#define  B_TAU_E1 132 
#define  B_TAU_E1C 131 
#define  B_TAU_E1D 130 
#define  B_TAU_G703 129 
#define  B_TAU_G703C 128 
 int CFG_A ; 
 int CFG_C ; 
 int /*<<< orphan*/  ct_e1_config (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ct_g703_config (TYPE_2__*,int) ; 

int ct_set_config (ct_board_t *b, int cfg)
{
	if (b->opt.cfg == cfg)
		return 0;
	switch (b->type) {
	case B_TAU_G703:
	case B_TAU_G703C:
	case B_TAU2_G703:
		if (cfg == CFG_C)
			return -1;
		ct_g703_config (b, cfg);
		return 0;
	case B_TAU_E1:
	case B_TAU_E1C:
	case B_TAU_E1D:
	case B_TAU2_E1:
	case B_TAU2_E1D:
		ct_e1_config (b, cfg);
		return 0;
	default:
		return cfg == CFG_A ? 0 : -1;
	}
}