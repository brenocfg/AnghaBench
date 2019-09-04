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
struct pathspec {int /*<<< orphan*/  nr; } ;
struct dir_struct {int nr; struct dir_entry** entries; } ;
struct dir_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_pathspec_matches_against_index (struct pathspec*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dir_path_match (int /*<<< orphan*/ *,struct dir_entry*,struct pathspec*,int,char*) ; 
 int /*<<< orphan*/  the_index ; 
 char* xcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *prune_directory(struct dir_struct *dir, struct pathspec *pathspec, int prefix)
{
	char *seen;
	int i;
	struct dir_entry **src, **dst;

	seen = xcalloc(pathspec->nr, 1);

	src = dst = dir->entries;
	i = dir->nr;
	while (--i >= 0) {
		struct dir_entry *entry = *src++;
		if (dir_path_match(&the_index, entry, pathspec, prefix, seen))
			*dst++ = entry;
	}
	dir->nr = dst - dir->entries;
	add_pathspec_matches_against_index(pathspec, &the_index, seen);
	return seen;
}