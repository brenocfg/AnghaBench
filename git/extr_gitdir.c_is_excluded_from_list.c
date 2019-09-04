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
struct exclude_list {int dummy; } ;
struct exclude {int flags; } ;

/* Variables and functions */
 int EXC_FLAG_NEGATIVE ; 
 struct exclude* last_exclude_matching_from_list (char const*,int,char const*,int*,struct exclude_list*,struct index_state*) ; 

int is_excluded_from_list(const char *pathname,
			  int pathlen, const char *basename, int *dtype,
			  struct exclude_list *el, struct index_state *istate)
{
	struct exclude *exclude;
	exclude = last_exclude_matching_from_list(pathname, pathlen, basename,
						  dtype, el, istate);
	if (exclude)
		return exclude->flags & EXC_FLAG_NEGATIVE ? 0 : 1;
	return -1; /* undecided */
}