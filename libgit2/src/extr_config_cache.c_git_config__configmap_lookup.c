#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct map_data {int default_value; int /*<<< orphan*/  map_count; scalar_t__ maps; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ git_configmap_item ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 struct map_data* _configmaps ; 
 int git_config__lookup_entry (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_config_entry_free (TYPE_1__*) ; 
 int git_config_lookup_map_value (int*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_config_parse_bool (int*,int /*<<< orphan*/ ) ; 

int git_config__configmap_lookup(int *out, git_config *config, git_configmap_item item)
{
	int error = 0;
	struct map_data *data = &_configmaps[(int)item];
	git_config_entry *entry;

	if ((error = git_config__lookup_entry(&entry, config, data->name, false)) < 0)
		return error;

	if (!entry)
		*out = data->default_value;
	else if (data->maps)
		error = git_config_lookup_map_value(
			out, data->maps, data->map_count, entry->value);
	else
		error = git_config_parse_bool(out, entry->value);

	git_config_entry_free(entry);
	return error;
}