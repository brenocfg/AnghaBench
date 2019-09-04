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
typedef  scalar_t__ int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GET_NO_ERRORS ; 
 int /*<<< orphan*/  get_entry (TYPE_1__**,int /*<<< orphan*/  const*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_entry_free (TYPE_1__*) ; 
 scalar_t__ git_config_parse_int32 (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_clear () ; 

int git_config__get_int_force(
	const git_config *cfg, const char *key, int fallback_value)
{
	int32_t val = (int32_t)fallback_value;
	git_config_entry *entry;

	get_entry(&entry, cfg, key, false, GET_NO_ERRORS);

	if (entry && git_config_parse_int32(&val, entry->value) < 0)
		git_error_clear();

	git_config_entry_free(entry);
	return (int)val;
}