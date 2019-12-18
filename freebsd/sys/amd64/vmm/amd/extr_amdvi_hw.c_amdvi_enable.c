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
typedef  int uint64_t ;
struct amdvi_softc {int ivhd_flag; int control; struct amdvi_softc* ctrl; } ;
struct amdvi_ctrl {int ivhd_flag; int control; struct amdvi_ctrl* ctrl; } ;

/* Variables and functions */
 int AMDVI_CTRL_CMD ; 
 int AMDVI_CTRL_COH ; 
 int AMDVI_CTRL_ELOG ; 
 int AMDVI_CTRL_ELOGINT ; 
 int AMDVI_CTRL_EN ; 
 int AMDVI_CTRL_HTT ; 
 int AMDVI_CTRL_INV_TO_1S ; 
 int AMDVI_CTRL_ISOC ; 
 int AMDVI_CTRL_PPW ; 
 int AMDVI_CTRL_RPPW ; 
 int IVHD_FLAG_COH ; 
 int IVHD_FLAG_HTT ; 
 int IVHD_FLAG_ISOC ; 
 int IVHD_FLAG_PPW ; 
 int IVHD_FLAG_RPPW ; 
 int /*<<< orphan*/  KASSERT (struct amdvi_softc*,char*) ; 
 struct amdvi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int ivhd_count ; 
 int /*<<< orphan*/ * ivhd_devs ; 

__attribute__((used)) static void
amdvi_enable(void)
{
	struct amdvi_ctrl *ctrl;
	struct amdvi_softc *softc;
	uint64_t val;
	int i;

	for (i = 0; i < ivhd_count; i++) {
		softc = device_get_softc(ivhd_devs[i]);
		KASSERT(softc, ("softc is NULL\n"));
		ctrl = softc->ctrl;
		KASSERT(ctrl, ("ctrl is NULL\n"));

		val = (	AMDVI_CTRL_EN 		|
			AMDVI_CTRL_CMD 		|
		    	AMDVI_CTRL_ELOG 	|
		    	AMDVI_CTRL_ELOGINT 	|
		    	AMDVI_CTRL_INV_TO_1S);

		if (softc->ivhd_flag & IVHD_FLAG_COH)
			val |= AMDVI_CTRL_COH;
		if (softc->ivhd_flag & IVHD_FLAG_HTT)
			val |= AMDVI_CTRL_HTT;
		if (softc->ivhd_flag & IVHD_FLAG_RPPW)
			val |= AMDVI_CTRL_RPPW;
		if (softc->ivhd_flag & IVHD_FLAG_PPW)
			val |= AMDVI_CTRL_PPW;
		if (softc->ivhd_flag & IVHD_FLAG_ISOC)
			val |= AMDVI_CTRL_ISOC;

		ctrl->control = val;
	}
}