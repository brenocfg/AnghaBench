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
struct brcmstb_gisb_arb_device {int valid_mask; char const** master_names; } ;

/* Variables and functions */
 int ffs (int) ; 
 int hweight_long (int) ; 

__attribute__((used)) static const char *
brcmstb_gisb_master_to_str(struct brcmstb_gisb_arb_device *gdev,
						u32 masters)
{
	u32 mask = gdev->valid_mask & masters;

	if (hweight_long(mask) != 1)
		return NULL;

	return gdev->master_names[ffs(mask) - 1];
}