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
struct index_state {int dummy; } ;
struct attr_check {TYPE_1__* items; } ;
struct TYPE_2__ {scalar_t__ value; } ;

/* Variables and functions */
 int DEFAULT_CONFLICT_MARKER_SIZE ; 
 int atoi (scalar_t__) ; 
 struct attr_check* attr_check_initl (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_check_attr (struct index_state*,char const*,struct attr_check*) ; 

int ll_merge_marker_size(struct index_state *istate, const char *path)
{
	static struct attr_check *check;
	int marker_size = DEFAULT_CONFLICT_MARKER_SIZE;

	if (!check)
		check = attr_check_initl("conflict-marker-size", NULL);
	git_check_attr(istate, path, check);
	if (check->items[0].value) {
		marker_size = atoi(check->items[0].value);
		if (marker_size <= 0)
			marker_size = DEFAULT_CONFLICT_MARKER_SIZE;
	}
	return marker_size;
}