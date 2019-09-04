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
 scalar_t__ git_color_config (char const*,char const*,void*) ; 
 int git_default_config (char const*,char const*,void*) ; 

int git_color_default_config(const char *var, const char *value, void *cb)
{
	if (git_color_config(var, value, cb) < 0)
		return -1;

	return git_default_config(var, value, cb);
}