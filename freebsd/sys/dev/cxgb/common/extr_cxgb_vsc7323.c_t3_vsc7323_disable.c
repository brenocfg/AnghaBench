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
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int MAC_DIRECTION_RX ; 
 int MAC_DIRECTION_TX ; 
 int /*<<< orphan*/  VSC_REG (int,int,int /*<<< orphan*/ ) ; 
 int elmr_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int t3_elmr_blk_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*,int) ; 

int t3_vsc7323_disable(adapter_t *adap, int port, int which)
{
	int ret;
	unsigned int v, orig;

	ret = t3_elmr_blk_read(adap, VSC_REG(1, port, 0), &v, 1);
	if (!ret) {
		orig = v;
		if (which & MAC_DIRECTION_TX)
			v &= ~1;
		if (which & MAC_DIRECTION_RX)
			v &= ~2;
		if (v != orig)
			ret = elmr_write(adap, VSC_REG(1, port, 0), v);
	}
	return ret;
}