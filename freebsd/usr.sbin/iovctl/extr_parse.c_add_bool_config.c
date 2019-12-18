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
 int /*<<< orphan*/  nvlist_add_bool (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  report_config_error (char const*,int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  ucl_object_toboolean_safe (int /*<<< orphan*/  const*,int*) ; 

__attribute__((used)) static void
add_bool_config(const char *key, const ucl_object_t *obj, nvlist_t *config)
{
	bool val;

	if (!ucl_object_toboolean_safe(obj, &val))
		report_config_error(key, obj, "bool");

	nvlist_add_bool(config, key, val);
}