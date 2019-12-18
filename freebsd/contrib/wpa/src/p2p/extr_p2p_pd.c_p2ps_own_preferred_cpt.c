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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static u8 p2ps_own_preferred_cpt(const u8 *cpt_priority, u8 req_cpt_mask)
{
	int i;

	for (i = 0; cpt_priority[i]; i++)
		if (req_cpt_mask & cpt_priority[i])
			return cpt_priority[i];

	return 0;
}