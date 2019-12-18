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
struct fingerprint_entry {int count; int /*<<< orphan*/  entry; } ;
struct fingerprint {int /*<<< orphan*/  map; struct fingerprint_entry* entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,unsigned int) ; 
 struct fingerprint_entry* hashmap_get_entry (int /*<<< orphan*/ *,struct fingerprint_entry*,struct fingerprint_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ isspace (char const) ; 
 unsigned int tolower (char const) ; 
 struct fingerprint_entry* xcalloc (int,int) ; 

__attribute__((used)) static void get_fingerprint(struct fingerprint *result,
			    const char *line_begin,
			    const char *line_end)
{
	unsigned int hash, c0 = 0, c1;
	const char *p;
	int max_map_entry_count = 1 + line_end - line_begin;
	struct fingerprint_entry *entry = xcalloc(max_map_entry_count,
		sizeof(struct fingerprint_entry));
	struct fingerprint_entry *found_entry;

	hashmap_init(&result->map, NULL, NULL, max_map_entry_count);
	result->entries = entry;
	for (p = line_begin; p <= line_end; ++p, c0 = c1) {
		/* Always terminate the string with whitespace.
		 * Normalise whitespace to 0, and normalise letters to
		 * lower case. This won't work for multibyte characters but at
		 * worst will match some unrelated characters.
		 */
		if ((p == line_end) || isspace(*p))
			c1 = 0;
		else
			c1 = tolower(*p);
		hash = c0 | (c1 << 8);
		/* Ignore whitespace pairs */
		if (hash == 0)
			continue;
		hashmap_entry_init(&entry->entry, hash);

		found_entry = hashmap_get_entry(&result->map, entry,
						/* member name */ entry, NULL);
		if (found_entry) {
			found_entry->count += 1;
		} else {
			entry->count = 1;
			hashmap_add(&result->map, &entry->entry);
			++entry;
		}
	}
}