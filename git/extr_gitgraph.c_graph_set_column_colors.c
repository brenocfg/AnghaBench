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
 char const** column_colors ; 
 unsigned short column_colors_max ; 

void graph_set_column_colors(const char **colors, unsigned short colors_max)
{
	column_colors = colors;
	column_colors_max = colors_max;
}