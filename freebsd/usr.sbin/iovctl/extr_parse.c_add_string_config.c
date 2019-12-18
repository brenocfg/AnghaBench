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
typedef  int /*<<< orphan*/  ucl_object_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  report_config_error (char const*,int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  ucl_object_tostring_safe (int /*<<< orphan*/  const*,char const**) ; 

__attribute__((used)) static void
add_string_config(const char *key, const ucl_object_t *obj, nvlist_t *config)
{
	const char *val;

	if (!ucl_object_tostring_safe(obj, &val))
		report_config_error(key, obj, "string");

	nvlist_add_string(config, key, val);
}