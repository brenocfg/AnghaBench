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
 char const* git_attributes_file ; 
 char* xdg_config_home (char*) ; 

__attribute__((used)) static const char *get_home_gitattributes(void)
{
	if (!git_attributes_file)
		git_attributes_file = xdg_config_home("attributes");

	return git_attributes_file;
}