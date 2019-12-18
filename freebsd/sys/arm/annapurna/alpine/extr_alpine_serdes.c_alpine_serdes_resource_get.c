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
typedef  size_t uint32_t ;

/* Variables and functions */
 size_t SERDES_NUM_GROUPS ; 
 int /*<<< orphan*/ * serdes_base ; 
 scalar_t__* serdes_grp_offset ; 

void *
alpine_serdes_resource_get(uint32_t group)
{
	void *base;

	base = NULL;
	if (group >= SERDES_NUM_GROUPS)
		return (NULL);

	if (serdes_base != NULL)
		base = (void *)((uintptr_t)serdes_base +
		    serdes_grp_offset[group]);

	return (base);
}