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
typedef  int /*<<< orphan*/  wchar_t ;
struct csnode {struct csnode* csn_left; struct csnode* csn_right; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ cset_rangecmp (struct csnode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct csnode *
cset_splay(struct csnode *t, wchar_t ch)
{
	struct csnode N, *l, *r, *y;

	/*
	 * Based on public domain code from Sleator.
	 */

	assert(t != NULL);

	N.csn_left = N.csn_right = NULL;
	l = r = &N;
	for (;;) {
		if (cset_rangecmp(t, ch) < 0) {
			if (t->csn_left != NULL &&
			    cset_rangecmp(t->csn_left, ch) < 0) {
				y = t->csn_left;
				t->csn_left = y->csn_right;
				y->csn_right = t;
				t = y;
			}
			if (t->csn_left == NULL)
				break;
			r->csn_left = t;
			r = t;
			t = t->csn_left;
		} else if (cset_rangecmp(t, ch) > 0) {
			if (t->csn_right != NULL &&
			    cset_rangecmp(t->csn_right, ch) > 0) {
				y = t->csn_right;
				t->csn_right = y->csn_left;
				y->csn_left = t;
				t = y;
			}
			if (t->csn_right == NULL)
				break;
			l->csn_right = t;
			l = t;
			t = t->csn_right;
		} else
			break;
	}
	l->csn_right = t->csn_left;
	r->csn_left = t->csn_right;
	t->csn_left = N.csn_right;
	t->csn_right = N.csn_left;
	return (t);
}