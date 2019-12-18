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
 int /*<<< orphan*/  is_submodule_populated_gently (char const*,int*) ; 

__attribute__((used)) static const char *default_name_or_path(const char *path_or_name)
{
	int error_code;

	if (!is_submodule_populated_gently(path_or_name, &error_code))
		return NULL;

	return path_or_name;
}