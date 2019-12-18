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
struct path_pattern {int flags; } ;
struct index_state {int dummy; } ;
struct dir_struct {int dummy; } ;

/* Variables and functions */
 int PATTERN_FLAG_NEGATIVE ; 
 struct path_pattern* last_matching_pattern (struct dir_struct*,struct index_state*,char const*,int*) ; 

int is_excluded(struct dir_struct *dir, struct index_state *istate,
		const char *pathname, int *dtype_p)
{
	struct path_pattern *pattern =
		last_matching_pattern(dir, istate, pathname, dtype_p);
	if (pattern)
		return pattern->flags & PATTERN_FLAG_NEGATIVE ? 0 : 1;
	return 0;
}