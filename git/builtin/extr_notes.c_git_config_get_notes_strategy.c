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
typedef  enum notes_merge_strategy { ____Placeholder_notes_merge_strategy } notes_merge_strategy ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ git_config_get_string (char const*,char**) ; 
 int /*<<< orphan*/  git_die_config (char const*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ parse_notes_merge_strategy (char*,int*) ; 

__attribute__((used)) static int git_config_get_notes_strategy(const char *key,
					 enum notes_merge_strategy *strategy)
{
	char *value;

	if (git_config_get_string(key, &value))
		return 1;
	if (parse_notes_merge_strategy(value, strategy))
		git_die_config(key, _("unknown notes merge strategy %s"), value);

	free(value);
	return 0;
}