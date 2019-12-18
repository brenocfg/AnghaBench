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

/* Variables and functions */
 unsigned int P2M_TOP_PER_PAGE ; 
 unsigned long* p2m_mid_missing_mfn ; 

__attribute__((used)) static void p2m_top_mfn_p_init(unsigned long **top)
{
	unsigned i;

	for (i = 0; i < P2M_TOP_PER_PAGE; i++)
		top[i] = p2m_mid_missing_mfn;
}