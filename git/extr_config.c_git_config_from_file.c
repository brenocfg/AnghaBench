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
typedef  int /*<<< orphan*/  config_fn_t ;

/* Variables and functions */
 int git_config_from_file_with_options (int /*<<< orphan*/ ,char const*,void*,int /*<<< orphan*/ *) ; 

int git_config_from_file(config_fn_t fn, const char *filename, void *data)
{
	return git_config_from_file_with_options(fn, filename, data, NULL);
}