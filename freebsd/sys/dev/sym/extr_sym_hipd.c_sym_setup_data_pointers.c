#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  hcb_p ;
typedef  TYPE_3__* ccb_p ;
struct TYPE_5__ {void* savep; void* goalp; void* lastp; } ;
struct TYPE_6__ {TYPE_1__ head; } ;
struct TYPE_7__ {int segments; TYPE_2__ phys; void* startp; int /*<<< orphan*/  host_flags; } ;

/* Variables and functions */
#define  CAM_DIR_IN 130 
#define  CAM_DIR_NONE 129 
#define  CAM_DIR_OUT 128 
 int /*<<< orphan*/  HF_DATA_IN ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SCRIPTA_BA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCRIPTB_BA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYM_LOCK_ASSERT (int /*<<< orphan*/ ) ; 
 void* cpu_to_scr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data_in2 ; 
 int /*<<< orphan*/  data_out2 ; 
 int /*<<< orphan*/  no_data ; 

__attribute__((used)) static void __inline
sym_setup_data_pointers(hcb_p np, ccb_p cp, int dir)
{
	u32 lastp, goalp;

	SYM_LOCK_ASSERT(MA_OWNED);

	/*
	 *  No segments means no data.
	 */
	if (!cp->segments)
		dir = CAM_DIR_NONE;

	/*
	 *  Set the data pointer.
	 */
	switch(dir) {
	case CAM_DIR_OUT:
		goalp = SCRIPTA_BA (np, data_out2) + 8;
		lastp = goalp - 8 - (cp->segments * (2*4));
		break;
	case CAM_DIR_IN:
		cp->host_flags |= HF_DATA_IN;
		goalp = SCRIPTA_BA (np, data_in2) + 8;
		lastp = goalp - 8 - (cp->segments * (2*4));
		break;
	case CAM_DIR_NONE:
	default:
		lastp = goalp = SCRIPTB_BA (np, no_data);
		break;
	}

	cp->phys.head.lastp = cpu_to_scr(lastp);
	cp->phys.head.goalp = cpu_to_scr(goalp);
	cp->phys.head.savep = cpu_to_scr(lastp);
	cp->startp	    = cp->phys.head.savep;
}