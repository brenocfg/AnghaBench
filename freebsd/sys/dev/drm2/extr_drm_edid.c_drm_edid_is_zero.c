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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */

__attribute__((used)) static bool drm_edid_is_zero(u8 *in_edid, int length)
{
	int i;
	u32 *raw_edid = (u32 *)in_edid;

	for (i = 0; i < length / 4; i++)
		if (*(raw_edid + i) != 0)
			return false;

	return true;
}