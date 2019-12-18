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
struct treesame_state {unsigned int nparents; } ;
struct rev_info {int /*<<< orphan*/  treesame; } ;
struct commit {int /*<<< orphan*/  object; int /*<<< orphan*/  parents; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_decoration (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct treesame_state*) ; 
 unsigned int commit_list_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_add (int,unsigned int) ; 
 struct treesame_state* xcalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct treesame_state *initialise_treesame(struct rev_info *revs, struct commit *commit)
{
	unsigned n = commit_list_count(commit->parents);
	struct treesame_state *st = xcalloc(1, st_add(sizeof(*st), n));
	st->nparents = n;
	add_decoration(&revs->treesame, &commit->object, st);
	return st;
}