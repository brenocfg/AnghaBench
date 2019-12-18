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
 unsigned int AL_EXTENT_SHIFT ; 
 unsigned int BM_BLOCK_SHIFT ; 
 unsigned int PAGE_SHIFT ; 

__attribute__((used)) static unsigned int al_extent_to_bm_page(unsigned int al_enr)
{
	return al_enr >>
		/* bit to page */
		((PAGE_SHIFT + 3) -
		/* al extent number to bit */
		 (AL_EXTENT_SHIFT - BM_BLOCK_SHIFT));
}