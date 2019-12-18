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
 int /*<<< orphan*/  CONFIG_ORIGIN_STDIN ; 
 int do_config_from_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static int git_config_from_stdin(config_fn_t fn, void *data)
{
	return do_config_from_file(fn, CONFIG_ORIGIN_STDIN, "", NULL, stdin,
				   data, NULL);
}