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
struct attr_stack {int dummy; } ;

/* Variables and functions */
 scalar_t__ GIT_ATTR_CHECKIN ; 
 scalar_t__ GIT_ATTR_CHECKOUT ; 
 scalar_t__ GIT_ATTR_INDEX ; 
 scalar_t__ direction ; 
 int /*<<< orphan*/  is_bare_repository () ; 
 struct attr_stack* read_attr_from_file (char const*,int) ; 
 struct attr_stack* read_attr_from_index (struct index_state const*,char const*,int) ; 
 struct attr_stack* xcalloc (int,int) ; 

__attribute__((used)) static struct attr_stack *read_attr(const struct index_state *istate,
				    const char *path, int macro_ok)
{
	struct attr_stack *res = NULL;

	if (direction == GIT_ATTR_INDEX) {
		res = read_attr_from_index(istate, path, macro_ok);
	} else if (!is_bare_repository()) {
		if (direction == GIT_ATTR_CHECKOUT) {
			res = read_attr_from_index(istate, path, macro_ok);
			if (!res)
				res = read_attr_from_file(path, macro_ok);
		} else if (direction == GIT_ATTR_CHECKIN) {
			res = read_attr_from_file(path, macro_ok);
			if (!res)
				/*
				 * There is no checked out .gitattributes file
				 * there, but we might have it in the index.
				 * We allow operation in a sparsely checked out
				 * work tree, so read from it.
				 */
				res = read_attr_from_index(istate, path, macro_ok);
		}
	}

	if (!res)
		res = xcalloc(1, sizeof(*res));
	return res;
}