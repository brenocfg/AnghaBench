#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct mwl_hal_priv {scalar_t__ mh_cmdbuf; } ;
struct mwl_hal {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * calTbl; } ;
typedef  TYPE_1__ HostCmd_FW_GET_CALTABLE ;

/* Variables and functions */
 struct mwl_hal_priv* MWLPRIV (struct mwl_hal*) ; 
 int /*<<< orphan*/  MWL_HAL_LOCK (struct mwl_hal_priv*) ; 
 int /*<<< orphan*/  MWL_HAL_UNLOCK (struct mwl_hal_priv*) ; 
 int mwlGetCalTable (struct mwl_hal_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
mwl_hal_getregioncode(struct mwl_hal *mh0, uint8_t *countryCode)
{
	struct mwl_hal_priv *mh = MWLPRIV(mh0);
	int retval;

	MWL_HAL_LOCK(mh);
	retval = mwlGetCalTable(mh, 0, 0);
	if (retval == 0) {
		const HostCmd_FW_GET_CALTABLE *pCmd =
		    (const HostCmd_FW_GET_CALTABLE *) mh->mh_cmdbuf;
		*countryCode = pCmd->calTbl[16];
	}
	MWL_HAL_UNLOCK(mh);
	return retval;
}