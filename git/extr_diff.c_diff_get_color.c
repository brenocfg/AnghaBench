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
typedef  enum color_diff { ____Placeholder_color_diff } color_diff ;

/* Variables and functions */
 char const** diff_colors ; 
 scalar_t__ want_color (int) ; 

const char *diff_get_color(int diff_use_color, enum color_diff ix)
{
	if (want_color(diff_use_color))
		return diff_colors[ix];
	return "";
}