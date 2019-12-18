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
struct csnode {struct csnode* csn_right; struct csnode* csn_left; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ cset_rangecmp (struct csnode*,int /*<<< orphan*/ ) ; 
 struct csnode* cset_splay (struct csnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct csnode*) ; 

__attribute__((used)) static struct csnode *
cset_delete(struct csnode *t, wchar_t ch)
{
	struct csnode *x;

	assert(t != NULL);
	t = cset_splay(t, ch);
	assert(cset_rangecmp(t, ch) == 0);
	if (t->csn_left == NULL)
		x = t->csn_right;
	else {
		x = cset_splay(t->csn_left, ch);
		x->csn_right = t->csn_right;
	}
	free(t);
	return x;
}