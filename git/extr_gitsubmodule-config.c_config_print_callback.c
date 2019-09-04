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
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static int config_print_callback(const char *var, const char *value, void *cb_data)
{
	char *wanted_key = cb_data;

	if (!strcmp(wanted_key, var))
		printf("%s\n", value);

	return 0;
}