#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dxfer_len; scalar_t__ data_ptr; } ;
union ccb {TYPE_1__ csio; } ;
struct TYPE_11__ {int /*<<< orphan*/  priv; } ;
struct TYPE_10__ {union ccb* ccb; } ;
struct TYPE_9__ {int eot; int /*<<< orphan*/  size; } ;
typedef  TYPE_2__* PSG ;
typedef  TYPE_3__* POS_CMDEXT ;
typedef  TYPE_4__* PCOMMAND ;
typedef  int /*<<< orphan*/  HPT_U8 ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  HPT_ASSERT (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  os_set_sgptr (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int os_buildsgl(PCOMMAND pCmd, PSG pSg, int logical)
{
	POS_CMDEXT ext = (POS_CMDEXT)pCmd->priv;
	union ccb *ccb = ext->ccb;

	if (logical) {
		os_set_sgptr(pSg, (HPT_U8 *)ccb->csio.data_ptr);
		pSg->size = ccb->csio.dxfer_len;
		pSg->eot = 1;
		return TRUE;
	}

	/* since we have provided physical sg, nobody will ask us to build physical sg */
	HPT_ASSERT(0);
	return FALSE;
}