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
typedef  size_t u32 ;

/* Variables and functions */
 char** clk_src_names ; 

__attribute__((used)) static void lpc18xx_fill_parent_names(const char **parent, u32 *id, int size)
{
	int i;

	for (i = 0; i < size; i++)
		parent[i] = clk_src_names[id[i]];
}