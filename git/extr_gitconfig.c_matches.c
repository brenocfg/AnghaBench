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
struct config_store_data {scalar_t__ value_regex; int do_not_match; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 scalar_t__ CONFIG_REGEX_NONE ; 
 int /*<<< orphan*/  regexec (scalar_t__,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int matches(const char *key, const char *value,
		   const struct config_store_data *store)
{
	if (strcmp(key, store->key))
		return 0; /* not ours */
	if (!store->value_regex)
		return 1; /* always matches */
	if (store->value_regex == CONFIG_REGEX_NONE)
		return 0; /* never matches */

	return store->do_not_match ^
		(value && !regexec(store->value_regex, value, 0, NULL, 0));
}