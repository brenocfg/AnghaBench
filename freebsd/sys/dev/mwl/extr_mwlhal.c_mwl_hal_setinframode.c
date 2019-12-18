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
struct mwl_hal_vap {int dummy; } ;
struct mwl_hal_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HostCmd_CMD_SET_INFRA_MODE ; 
 int HostCmd_FW_SET_INFRA_MODE ; 
 struct mwl_hal_priv* MWLVAP (struct mwl_hal_vap*) ; 
 int /*<<< orphan*/  MWL_HAL_LOCK (struct mwl_hal_priv*) ; 
 int /*<<< orphan*/  MWL_HAL_UNLOCK (struct mwl_hal_priv*) ; 
 int /*<<< orphan*/  _VCMD_SETUP (struct mwl_hal_vap*,int,int,int /*<<< orphan*/ ) ; 
 int mwlExecuteCmd (struct mwl_hal_priv*,int /*<<< orphan*/ ) ; 
 int pCmd ; 

int
mwl_hal_setinframode(struct mwl_hal_vap *vap)
{
	struct mwl_hal_priv *mh = MWLVAP(vap);
	HostCmd_FW_SET_INFRA_MODE *pCmd;
	int retval;

	MWL_HAL_LOCK(mh);
	_VCMD_SETUP(vap, pCmd, HostCmd_FW_SET_INFRA_MODE,
		HostCmd_CMD_SET_INFRA_MODE);

	retval = mwlExecuteCmd(mh, HostCmd_CMD_SET_INFRA_MODE);
	MWL_HAL_UNLOCK(mh);
	return retval;
}