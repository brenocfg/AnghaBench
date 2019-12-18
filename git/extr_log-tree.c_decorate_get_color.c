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
typedef  enum decoration_type { ____Placeholder_decoration_type } decoration_type ;

/* Variables and functions */
 char const** decoration_colors ; 
 scalar_t__ want_color (int) ; 

__attribute__((used)) static const char *decorate_get_color(int decorate_use_color, enum decoration_type ix)
{
	if (want_color(decorate_use_color))
		return decoration_colors[ix];
	return "";
}