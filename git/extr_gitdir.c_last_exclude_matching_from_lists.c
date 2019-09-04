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
struct index_state {int dummy; } ;
struct exclude_list_group {int nr; int /*<<< orphan*/ * el; } ;
struct exclude {int dummy; } ;
struct dir_struct {struct exclude_list_group* exclude_list_group; } ;

/* Variables and functions */
 int EXC_CMDL ; 
 int EXC_FILE ; 
 struct exclude* last_exclude_matching_from_list (char const*,int,char const*,int*,int /*<<< orphan*/ *,struct index_state*) ; 

__attribute__((used)) static struct exclude *last_exclude_matching_from_lists(struct dir_struct *dir,
							struct index_state *istate,
		const char *pathname, int pathlen, const char *basename,
		int *dtype_p)
{
	int i, j;
	struct exclude_list_group *group;
	struct exclude *exclude;
	for (i = EXC_CMDL; i <= EXC_FILE; i++) {
		group = &dir->exclude_list_group[i];
		for (j = group->nr - 1; j >= 0; j--) {
			exclude = last_exclude_matching_from_list(
				pathname, pathlen, basename, dtype_p,
				&group->el[j], istate);
			if (exclude)
				return exclude;
		}
	}
	return NULL;
}