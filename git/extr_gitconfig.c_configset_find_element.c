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
struct config_set_element {char* key; } ;
struct config_set {int /*<<< orphan*/  config_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ git_config_parse_key (char const*,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_entry_init (struct config_set_element*,int /*<<< orphan*/ ) ; 
 struct config_set_element* hashmap_get (int /*<<< orphan*/ *,struct config_set_element*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strhash (char*) ; 

__attribute__((used)) static struct config_set_element *configset_find_element(struct config_set *cs, const char *key)
{
	struct config_set_element k;
	struct config_set_element *found_entry;
	char *normalized_key;
	/*
	 * `key` may come from the user, so normalize it before using it
	 * for querying entries from the hashmap.
	 */
	if (git_config_parse_key(key, &normalized_key, NULL))
		return NULL;

	hashmap_entry_init(&k, strhash(normalized_key));
	k.key = normalized_key;
	found_entry = hashmap_get(&cs->config_hash, &k, NULL);
	free(normalized_key);
	return found_entry;
}