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
typedef  unsigned int u32 ;
struct mdio_ops {int (* write ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int (* read ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ;} ;
typedef  int /*<<< orphan*/  adapter_t ;
struct TYPE_2__ {struct mdio_ops* mdio_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELMR_ADDR ; 
 int /*<<< orphan*/  ELMR_DATA_HI ; 
 int /*<<< orphan*/  ELMR_DATA_LO ; 
 int /*<<< orphan*/  ELMR_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ELMR_MDIO_ADDR ; 
 int /*<<< orphan*/  ELMR_STAT ; 
 int /*<<< orphan*/  ELMR_UNLOCK (int /*<<< orphan*/ *) ; 
 int ETIMEDOUT ; 
 TYPE_1__* adapter_info (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

int t3_elmr_blk_read(adapter_t *adap, int start, u32 *vals, int n)
{
	int i, ret;
	unsigned int v;
	const struct mdio_ops *mo = adapter_info(adap)->mdio_ops;

	ELMR_LOCK(adap);

	ret = mo->write(adap, ELMR_MDIO_ADDR, 0, ELMR_ADDR, start);
	if (ret)
		goto out;

	for (i = 0; i < 5; i++) {
		ret = mo->read(adap, ELMR_MDIO_ADDR, 0, ELMR_STAT, &v);
		if (ret)
			goto out;
		if (v == 1)
			break;
		udelay(5);
	}
	if (v != 1) {
		ret = -ETIMEDOUT;
		goto out;
	}

	for ( ; !ret && n; n--, vals++) {
		ret = mo->read(adap, ELMR_MDIO_ADDR, 0, ELMR_DATA_LO, vals);
		if (!ret) {
			ret = mo->read(adap, ELMR_MDIO_ADDR, 0, ELMR_DATA_HI,
				       &v);
			*vals |= v << 16;
		}
	}
out:	ELMR_UNLOCK(adap);
	return ret;
}