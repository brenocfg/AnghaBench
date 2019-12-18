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
struct edid {int extensions; } ;

/* Variables and functions */
 int EDID_LENGTH ; 
 int /*<<< orphan*/  drm_edid_block_valid (int /*<<< orphan*/ *,int,int) ; 

bool drm_edid_is_valid(struct edid *edid)
{
	int i;
	u8 *raw = (u8 *)edid;

	if (!edid)
		return false;

	for (i = 0; i <= edid->extensions; i++)
		if (!drm_edid_block_valid(raw + i * EDID_LENGTH, i, true))
			return false;

	return true;
}