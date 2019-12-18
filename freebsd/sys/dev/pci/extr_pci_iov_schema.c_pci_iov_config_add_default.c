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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  nvlist_add_binary (int /*<<< orphan*/ *,char const*,void const*,size_t) ; 
 int /*<<< orphan*/  nvlist_add_bool (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_exists_binary (int /*<<< orphan*/  const*,char*) ; 
 scalar_t__ nvlist_exists_bool (int /*<<< orphan*/  const*,char*) ; 
 scalar_t__ nvlist_exists_number (int /*<<< orphan*/  const*,char*) ; 
 scalar_t__ nvlist_exists_nvlist (int /*<<< orphan*/  const*,char*) ; 
 scalar_t__ nvlist_exists_string (int /*<<< orphan*/  const*,char*) ; 
 void* nvlist_get_binary (int /*<<< orphan*/  const*,char*,size_t*) ; 
 int /*<<< orphan*/  nvlist_get_bool (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  nvlist_get_number (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  nvlist_get_nvlist (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  nvlist_get_string (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
pci_iov_config_add_default(const nvlist_t *param_schema, const char *name,
    nvlist_t *config)
{
	const void *binary;
	size_t len;

	if (nvlist_exists_binary(param_schema, "default")) {
		binary = nvlist_get_binary(param_schema, "default", &len);
		nvlist_add_binary(config, name, binary, len);
	} else if (nvlist_exists_bool(param_schema, "default"))
		nvlist_add_bool(config, name,
		    nvlist_get_bool(param_schema, "default"));
	else if (nvlist_exists_number(param_schema, "default"))
		nvlist_add_number(config, name,
		    nvlist_get_number(param_schema, "default"));
	else if (nvlist_exists_nvlist(param_schema, "default"))
		nvlist_add_nvlist(config, name,
		    nvlist_get_nvlist(param_schema, "default"));
	else if (nvlist_exists_string(param_schema, "default"))
		nvlist_add_string(config, name,
		    nvlist_get_string(param_schema, "default"));
	else
		panic("Unexpected nvlist type");
}