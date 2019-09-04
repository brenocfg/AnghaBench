#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct commit_list {int dummy; } ;
struct TYPE_2__ {struct object_id oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  NORMAL ; 
 int /*<<< orphan*/  REVERSED ; 
 struct commit_list* get_merge_bases (struct commit*,struct commit*) ; 
 int /*<<< orphan*/  get_oid_committish (char const*,struct object_id*) ; 
 struct commit* lookup_commit_reference (int /*<<< orphan*/ ,struct object_id*) ; 
 struct commit* pop_commit (struct commit_list**) ; 
 int /*<<< orphan*/  show_rev (int /*<<< orphan*/ ,struct object_id*,char const*) ; 
 char* strstr (char const*,char*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int try_difference(const char *arg)
{
	char *dotdot;
	struct object_id start_oid;
	struct object_id end_oid;
	const char *end;
	const char *start;
	int symmetric;
	static const char head_by_default[] = "HEAD";

	if (!(dotdot = strstr(arg, "..")))
		return 0;
	end = dotdot + 2;
	start = arg;
	symmetric = (*end == '.');

	*dotdot = 0;
	end += symmetric;

	if (!*end)
		end = head_by_default;
	if (dotdot == arg)
		start = head_by_default;

	if (start == head_by_default && end == head_by_default &&
	    !symmetric) {
		/*
		 * Just ".."?  That is not a range but the
		 * pathspec for the parent directory.
		 */
		*dotdot = '.';
		return 0;
	}

	if (!get_oid_committish(start, &start_oid) && !get_oid_committish(end, &end_oid)) {
		show_rev(NORMAL, &end_oid, end);
		show_rev(symmetric ? NORMAL : REVERSED, &start_oid, start);
		if (symmetric) {
			struct commit_list *exclude;
			struct commit *a, *b;
			a = lookup_commit_reference(the_repository, &start_oid);
			b = lookup_commit_reference(the_repository, &end_oid);
			if (!a || !b) {
				*dotdot = '.';
				return 0;
			}
			exclude = get_merge_bases(a, b);
			while (exclude) {
				struct commit *commit = pop_commit(&exclude);
				show_rev(REVERSED, &commit->object.oid, NULL);
			}
		}
		*dotdot = '.';
		return 1;
	}
	*dotdot = '.';
	return 0;
}