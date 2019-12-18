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
typedef  unsigned int u32 ;

/* Variables and functions */

__attribute__((used)) static bool cc_is_icv_frag(unsigned int sgl_nents, unsigned int authsize,
			   u32 last_entry_data_size)
{
	return ((sgl_nents > 1) && (last_entry_data_size < authsize));
}