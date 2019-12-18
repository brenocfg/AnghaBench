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
typedef  enum color_transport { ____Placeholder_color_transport } color_transport ;

/* Variables and functions */
 char const** transport_colors ; 
 int /*<<< orphan*/  transport_use_color ; 
 scalar_t__ want_color_stderr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *transport_get_color(enum color_transport ix)
{
	if (want_color_stderr(transport_use_color))
		return transport_colors[ix];
	return "";
}