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
struct pair_entry {char* left; char* right; int /*<<< orphan*/  entry; } ;
struct hashmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX_ALLOC_STR (struct pair_entry*,char const*,char const*) ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (struct pair_entry*) ; 
 int /*<<< orphan*/  hashmap_add (struct hashmap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pair_entry* hashmap_get_entry (struct hashmap*,struct pair_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strhash (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_left_or_right(struct hashmap *map, const char *path,
			      const char *content, int is_right)
{
	struct pair_entry *e, *existing;

	FLEX_ALLOC_STR(e, path, path);
	hashmap_entry_init(&e->entry, strhash(path));
	existing = hashmap_get_entry(map, e, entry, NULL);
	if (existing) {
		free(e);
		e = existing;
	} else {
		e->left[0] = e->right[0] = '\0';
		hashmap_add(map, &e->entry);
	}
	strlcpy(is_right ? e->right : e->left, content, PATH_MAX);
}