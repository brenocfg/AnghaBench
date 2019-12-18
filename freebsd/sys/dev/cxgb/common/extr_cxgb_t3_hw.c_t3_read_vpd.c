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
typedef  int u32 ;
struct generic_vpd {int len; int /*<<< orphan*/ * data; scalar_t__ offset; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int t3_seeprom_read (int /*<<< orphan*/ *,scalar_t__,int*) ; 

int t3_read_vpd(adapter_t *adapter, struct generic_vpd *vpd)
{
	u32 i, ret;

	for (i = 0; i < vpd->len; i += 4) {
		ret = t3_seeprom_read(adapter, vpd->offset + i,
				      (u32 *) &(vpd->data[i]));
		if (ret)
			return ret;
	}

	return 0;
}