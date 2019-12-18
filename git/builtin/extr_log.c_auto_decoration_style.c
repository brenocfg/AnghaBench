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
 int DECORATE_SHORT_REFS ; 
 scalar_t__ session_is_interactive () ; 

__attribute__((used)) static int auto_decoration_style(void)
{
	return session_is_interactive() ? DECORATE_SHORT_REFS : 0;
}