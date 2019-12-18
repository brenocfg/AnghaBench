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
struct dh_group {int id; } ;

/* Variables and functions */
 size_t NUM_DH_GROUPS ; 
 struct dh_group const* dh_groups ; 

const struct dh_group * dh_groups_get(int id)
{
	size_t i;

	for (i = 0; i < NUM_DH_GROUPS; i++) {
		if (dh_groups[i].id == id)
			return &dh_groups[i];
	}
	return NULL;
}