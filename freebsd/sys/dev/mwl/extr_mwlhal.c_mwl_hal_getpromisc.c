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
struct mwl_hal_priv {int dummy; } ;
struct mwl_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACREG_REG_PROMISCUOUS ; 
 struct mwl_hal_priv* MWLPRIV (struct mwl_hal*) ; 
 int /*<<< orphan*/  MWL_HAL_LOCK (struct mwl_hal_priv*) ; 
 int /*<<< orphan*/  MWL_HAL_UNLOCK (struct mwl_hal_priv*) ; 
 int RD4 (struct mwl_hal_priv*,int /*<<< orphan*/ ) ; 

int
mwl_hal_getpromisc(struct mwl_hal *mh0)
{
	struct mwl_hal_priv *mh = MWLPRIV(mh0);
	uint32_t v;

	MWL_HAL_LOCK(mh);
	v = RD4(mh, MACREG_REG_PROMISCUOUS);
	MWL_HAL_UNLOCK(mh);
	return (v & 1) != 0;
}