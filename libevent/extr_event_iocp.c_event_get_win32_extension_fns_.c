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
struct win32_extension_fns {int dummy; } ;

/* Variables and functions */
 struct win32_extension_fns const the_extension_fns ; 

const struct win32_extension_fns *
event_get_win32_extension_fns_(void)
{
	return &the_extension_fns;
}