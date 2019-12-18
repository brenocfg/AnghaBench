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
struct cache_entry {char const* name; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int WRITE_TREE_SILENT ; 
 scalar_t__ ce_stage (struct cache_entry const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static int verify_cache(struct cache_entry **cache,
			int entries, int flags)
{
	int i, funny;
	int silent = flags & WRITE_TREE_SILENT;

	/* Verify that the tree is merged */
	funny = 0;
	for (i = 0; i < entries; i++) {
		const struct cache_entry *ce = cache[i];
		if (ce_stage(ce)) {
			if (silent)
				return -1;
			if (10 < ++funny) {
				fprintf(stderr, "...\n");
				break;
			}
			fprintf(stderr, "%s: unmerged (%s)\n",
				ce->name, oid_to_hex(&ce->oid));
		}
	}
	if (funny)
		return -1;

	/* Also verify that the cache does not have path and path/file
	 * at the same time.  At this point we know the cache has only
	 * stage 0 entries.
	 */
	funny = 0;
	for (i = 0; i < entries - 1; i++) {
		/* path/file always comes after path because of the way
		 * the cache is sorted.  Also path can appear only once,
		 * which means conflicting one would immediately follow.
		 */
		const char *this_name = cache[i]->name;
		const char *next_name = cache[i+1]->name;
		int this_len = strlen(this_name);
		if (this_len < strlen(next_name) &&
		    strncmp(this_name, next_name, this_len) == 0 &&
		    next_name[this_len] == '/') {
			if (10 < ++funny) {
				fprintf(stderr, "...\n");
				break;
			}
			fprintf(stderr, "You have both %s and %s\n",
				this_name, next_name);
		}
	}
	if (funny)
		return -1;
	return 0;
}