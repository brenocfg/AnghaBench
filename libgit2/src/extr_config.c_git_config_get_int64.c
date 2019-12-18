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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GET_ALL_ERRORS ; 
 int get_entry (TYPE_1__**,int /*<<< orphan*/  const*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_entry_free (TYPE_1__*) ; 
 int git_config_parse_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int git_config_get_int64(int64_t *out, const git_config *cfg, const char *name)
{
	git_config_entry *entry;
	int ret;

	if ((ret = get_entry(&entry, cfg, name, true, GET_ALL_ERRORS)) < 0)
		return ret;

	ret = git_config_parse_int64(out, entry->value);
	git_config_entry_free(entry);

	return ret;
}