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
typedef  scalar_t__ wint_t ;
struct cmapnode {scalar_t__ cmn_from; struct cmapnode* cmn_left; struct cmapnode* cmn_right; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cmapnode *
cmap_splay(struct cmapnode *t, wint_t ch)
{
	struct cmapnode N, *l, *r, *y;

	/*
	 * Based on public domain code from Sleator.
	 */

	assert(t != NULL);

	N.cmn_left = N.cmn_right = NULL;
	l = r = &N;
	for (;;) {
		if (ch < t->cmn_from) {
			if (t->cmn_left != NULL &&
			    ch < t->cmn_left->cmn_from) {
				y = t->cmn_left;
				t->cmn_left = y->cmn_right;
				y->cmn_right = t;
				t = y;
			}
			if (t->cmn_left == NULL)
				break;
			r->cmn_left = t;
			r = t;
			t = t->cmn_left;
		} else if (ch > t->cmn_from) {
			if (t->cmn_right != NULL &&
			    ch > t->cmn_right->cmn_from) {
				y = t->cmn_right;
				t->cmn_right = y->cmn_left;
				y->cmn_left = t;
				t = y;
			}
			if (t->cmn_right == NULL)
				break;
			l->cmn_right = t;
			l = t;
			t = t->cmn_right;
		} else
			break;
	}
	l->cmn_right = t->cmn_left;
	r->cmn_left = t->cmn_right;
	t->cmn_left = N.cmn_right;
	t->cmn_right = N.cmn_left;
	return (t);
}