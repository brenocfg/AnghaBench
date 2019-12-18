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
struct rev_info {int /*<<< orphan*/  merge_simplification; } ;
struct merge_simplify_state {int dummy; } ;
struct commit {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_decoration (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct merge_simplify_state*) ; 
 struct merge_simplify_state* lookup_decoration (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct merge_simplify_state* xcalloc (int,int) ; 

__attribute__((used)) static struct merge_simplify_state *locate_simplify_state(struct rev_info *revs, struct commit *commit)
{
	struct merge_simplify_state *st;

	st = lookup_decoration(&revs->merge_simplification, &commit->object);
	if (!st) {
		st = xcalloc(1, sizeof(*st));
		add_decoration(&revs->merge_simplification, &commit->object, st);
	}
	return st;
}