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
 int of_property_read_string (int /*<<< orphan*/ ,char*,char const**) ; 
 int of_property_read_string_index (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  of_root ; 

const char *get_system_type(void)
{
	const char *str;
	int err;

	err = of_property_read_string(of_root, "model", &str);
	if (!err)
		return str;

	err = of_property_read_string_index(of_root, "compatible", 0, &str);
	if (!err)
		return str;

	return "Unknown";
}