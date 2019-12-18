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
struct path_pattern {int dummy; } ;
struct index_state {int dummy; } ;
struct dir_struct {struct path_pattern* pattern; } ;

/* Variables and functions */
 struct path_pattern* last_matching_pattern_from_lists (struct dir_struct*,struct index_state*,char const*,int,char const*,int*) ; 
 int /*<<< orphan*/  prep_exclude (struct dir_struct*,struct index_state*,char const*,int) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

struct path_pattern *last_matching_pattern(struct dir_struct *dir,
				      struct index_state *istate,
				      const char *pathname,
				      int *dtype_p)
{
	int pathlen = strlen(pathname);
	const char *basename = strrchr(pathname, '/');
	basename = (basename) ? basename+1 : pathname;

	prep_exclude(dir, istate, pathname, basename-pathname);

	if (dir->pattern)
		return dir->pattern;

	return last_matching_pattern_from_lists(dir, istate, pathname, pathlen,
			basename, dtype_p);
}