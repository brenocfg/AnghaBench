#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int i1; int chg1; scalar_t__ mode; struct TYPE_4__* next; } ;
typedef  TYPE_1__ xdmerge_t ;
typedef  int /*<<< orphan*/  xdfenv_t ;

/* Variables and functions */
 scalar_t__ lines_contain_alnum (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  xdl_merge_two_conflicts (TYPE_1__*) ; 

__attribute__((used)) static int xdl_simplify_non_conflicts(xdfenv_t *xe1, xdmerge_t *m,
				      int simplify_if_no_alnum)
{
	int result = 0;

	if (!m)
		return result;
	for (;;) {
		xdmerge_t *next_m = m->next;
		int begin, end;

		if (!next_m)
			return result;

		begin = m->i1 + m->chg1;
		end = next_m->i1;

		if (m->mode != 0 || next_m->mode != 0 ||
		    (end - begin > 3 &&
		     (!simplify_if_no_alnum ||
		      lines_contain_alnum(xe1, begin, end - begin)))) {
			m = next_m;
		} else {
			result++;
			xdl_merge_two_conflicts(m);
		}
	}
}