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
struct exclude {int flags; } ;
struct dir_struct {int dummy; } ;

/* Variables and functions */
 int EXC_FLAG_NEGATIVE ; 
 struct exclude* last_exclude_matching (struct dir_struct*,struct index_state*,char const*,int*) ; 

int is_excluded(struct dir_struct *dir, struct index_state *istate,
		const char *pathname, int *dtype_p)
{
	struct exclude *exclude =
		last_exclude_matching(dir, istate, pathname, dtype_p);
	if (exclude)
		return exclude->flags & EXC_FLAG_NEGATIVE ? 0 : 1;
	return 0;
}