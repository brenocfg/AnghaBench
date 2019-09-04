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
struct index_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_pathspec_matches_against_index (struct pathspec const*,struct index_state const*,char*) ; 
 char* xcalloc (int /*<<< orphan*/ ,int) ; 

char *find_pathspecs_matching_against_index(const struct pathspec *pathspec,
					    const struct index_state *istate)
{
	char *seen = xcalloc(pathspec->nr, 1);
	add_pathspec_matches_against_index(pathspec, istate, seen);
	return seen;
}