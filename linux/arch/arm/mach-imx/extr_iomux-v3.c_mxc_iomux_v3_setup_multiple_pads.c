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
typedef  int /*<<< orphan*/  iomux_v3_cfg_t ;

/* Variables and functions */
 int mxc_iomux_v3_setup_pad (int /*<<< orphan*/  const) ; 

int mxc_iomux_v3_setup_multiple_pads(const iomux_v3_cfg_t *pad_list,
		unsigned count)
{
	const iomux_v3_cfg_t *p = pad_list;
	int i;
	int ret;

	for (i = 0; i < count; i++) {
		ret = mxc_iomux_v3_setup_pad(*p);
		if (ret)
			return ret;
		p++;
	}
	return 0;
}