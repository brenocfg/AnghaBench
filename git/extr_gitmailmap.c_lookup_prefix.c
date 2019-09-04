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
struct string_list_item {int /*<<< orphan*/ * string; } ;
struct string_list {int nr; struct string_list_item* items; } ;

/* Variables and functions */
 int string_list_find_insert_index (struct string_list*,char const*,int) ; 
 int strncasecmp (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static struct string_list_item *lookup_prefix(struct string_list *map,
					      const char *string, size_t len)
{
	int i = string_list_find_insert_index(map, string, 1);
	if (i < 0) {
		/* exact match */
		i = -1 - i;
		if (!string[len])
			return &map->items[i];
		/*
		 * that map entry matches exactly to the string, including
		 * the cruft at the end beyond "len".  That is not a match
		 * with string[0:len] that we are looking for.
		 */
	} else if (!string[len]) {
		/*
		 * asked with the whole string, and got nothing.  No
		 * matching entry can exist in the map.
		 */
		return NULL;
	}

	/*
	 * i is at the exact match to an overlong key, or location the
	 * overlong key would be inserted, which must come after the
	 * real location of the key if one exists.
	 */
	while (0 <= --i && i < map->nr) {
		int cmp = strncasecmp(map->items[i].string, string, len);
		if (cmp < 0)
			/*
			 * "i" points at a key definitely below the prefix;
			 * the map does not have string[0:len] in it.
			 */
			break;
		else if (!cmp && !map->items[i].string[len])
			/* found it */
			return &map->items[i];
		/*
		 * otherwise, the string at "i" may be string[0:len]
		 * followed by a string that sorts later than string[len:];
		 * keep trying.
		 */
	}
	return NULL;
}