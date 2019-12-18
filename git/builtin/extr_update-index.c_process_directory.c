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
struct stat {int dummy; } ;
struct object_id {int dummy; } ;
struct cache_entry {char* name; int /*<<< orphan*/  ce_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 struct cache_entry** active_cache ; 
 int active_nr ; 
 int add_one_path (struct cache_entry const*,char const*,int,struct stat*) ; 
 int cache_name_pos (char const*,int) ; 
 int error (char*,char const*) ; 
 int remove_one_path (char const*) ; 
 scalar_t__ resolve_gitlink_ref (char const*,char*,struct object_id*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

__attribute__((used)) static int process_directory(const char *path, int len, struct stat *st)
{
	struct object_id oid;
	int pos = cache_name_pos(path, len);

	/* Exact match: file or existing gitlink */
	if (pos >= 0) {
		const struct cache_entry *ce = active_cache[pos];
		if (S_ISGITLINK(ce->ce_mode)) {

			/* Do nothing to the index if there is no HEAD! */
			if (resolve_gitlink_ref(path, "HEAD", &oid) < 0)
				return 0;

			return add_one_path(ce, path, len, st);
		}
		/* Should this be an unconditional error? */
		return remove_one_path(path);
	}

	/* Inexact match: is there perhaps a subdirectory match? */
	pos = -pos-1;
	while (pos < active_nr) {
		const struct cache_entry *ce = active_cache[pos++];

		if (strncmp(ce->name, path, len))
			break;
		if (ce->name[len] > '/')
			break;
		if (ce->name[len] < '/')
			continue;

		/* Subdirectory match - error out */
		return error("%s: is a directory - add individual files instead", path);
	}

	/* No match - should we add it as a gitlink? */
	if (!resolve_gitlink_ref(path, "HEAD", &oid))
		return add_one_path(NULL, path, len, st);

	/* Error out. */
	return error("%s: is a directory - add files inside instead", path);
}