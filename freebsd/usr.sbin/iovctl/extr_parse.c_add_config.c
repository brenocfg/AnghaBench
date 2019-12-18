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
 int /*<<< orphan*/  TYPE_SCHEMA_NAME ; 
 int /*<<< orphan*/  UINT16_MAX ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  UINT8_MAX ; 
 int /*<<< orphan*/  add_bool_config (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_string_config (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_uint_config (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_unicast_mac_config (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 char* nvlist_get_string (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static void
add_config(const char *key, const ucl_object_t *obj, nvlist_t *config,
    const nvlist_t *schema)
{
	const char *type;

	type = nvlist_get_string(schema, TYPE_SCHEMA_NAME);

	if (strcasecmp(type, "bool") == 0)
		add_bool_config(key, obj, config);
	else if (strcasecmp(type, "string") == 0)
		add_string_config(key, obj, config);
	else if (strcasecmp(type, "uint8_t") == 0)
		add_uint_config(key, obj, config, type, UINT8_MAX);
	else if (strcasecmp(type, "uint16_t") == 0)
		add_uint_config(key, obj, config, type, UINT16_MAX);
	else if (strcasecmp(type, "uint32_t") == 0)
		add_uint_config(key, obj, config, type, UINT32_MAX);
	else if (strcasecmp(type, "uint64_t") == 0)
		add_uint_config(key, obj, config, type, UINT64_MAX);
	else if (strcasecmp(type, "unicast-mac") == 0)
		add_unicast_mac_config(key, obj, config);
	else
		errx(1, "Unexpected type '%s' in schema", type);
}