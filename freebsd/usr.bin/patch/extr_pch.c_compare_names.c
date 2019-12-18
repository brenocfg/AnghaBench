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
struct file_name {char* path; int /*<<< orphan*/  exists; } ;

/* Variables and functions */
 int INDEX_FILE ; 
 int OLD_FILE ; 
 size_t SIZE_MAX ; 
 char* basename (char*) ; 
 size_t num_components (char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static char *
compare_names(const struct file_name *names, bool assume_exists)
{
	size_t min_components, min_baselen, min_len, tmp;
	char *best = NULL;
	char *path;
	int i;

	/*
	 * The "best" name is the one with the fewest number of path
	 * components, the shortest basename length, and the shortest
	 * overall length (in that order).  We only use the Index: file
	 * if neither of the old or new files could be intuited from
	 * the diff header.
	 */
	min_components = min_baselen = min_len = SIZE_MAX;
	for (i = INDEX_FILE; i >= OLD_FILE; i--) {
		path = names[i].path;
		if (path == NULL || (!names[i].exists && !assume_exists))
			continue;
		if ((tmp = num_components(path)) > min_components)
			continue;
		if (tmp < min_components) {
			min_components = tmp;
			best = path;
		}
		if ((tmp = strlen(basename(path))) > min_baselen)
			continue;
		if (tmp < min_baselen) {
			min_baselen = tmp;
			best = path;
		}
		if ((tmp = strlen(path)) > min_len)
			continue;
		min_len = tmp;
		best = path;
	}
	return best;
}