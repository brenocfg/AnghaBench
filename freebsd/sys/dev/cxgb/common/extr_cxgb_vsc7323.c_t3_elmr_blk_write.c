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
typedef  int u32 ;
struct mdio_ops {int (* write ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
typedef  int /*<<< orphan*/  adapter_t ;
struct TYPE_2__ {struct mdio_ops* mdio_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELMR_ADDR ; 
 int /*<<< orphan*/  ELMR_DATA_HI ; 
 int /*<<< orphan*/  ELMR_DATA_LO ; 
 int /*<<< orphan*/  ELMR_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ELMR_MDIO_ADDR ; 
 int /*<<< orphan*/  ELMR_UNLOCK (int /*<<< orphan*/ *) ; 
 TYPE_1__* adapter_info (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 

int t3_elmr_blk_write(adapter_t *adap, int start, const u32 *vals, int n)
{
	int ret;
	const struct mdio_ops *mo = adapter_info(adap)->mdio_ops;

	ELMR_LOCK(adap);
	ret = mo->write(adap, ELMR_MDIO_ADDR, 0, ELMR_ADDR, start);
	for ( ; !ret && n; n--, vals++) {
		ret = mo->write(adap, ELMR_MDIO_ADDR, 0, ELMR_DATA_LO,
				*vals & 0xffff);
		if (!ret)
			ret = mo->write(adap, ELMR_MDIO_ADDR, 0, ELMR_DATA_HI,
					*vals >> 16);
	}
	ELMR_UNLOCK(adap);
	return ret;
}