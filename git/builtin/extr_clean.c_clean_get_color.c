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
typedef  enum color_clean { ____Placeholder_color_clean } color_clean ;

/* Variables and functions */
 char const** clean_colors ; 
 int /*<<< orphan*/  clean_use_color ; 
 scalar_t__ want_color (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *clean_get_color(enum color_clean ix)
{
	if (want_color(clean_use_color))
		return clean_colors[ix];
	return "";
}