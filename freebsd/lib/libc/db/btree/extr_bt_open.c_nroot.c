#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pgno_t ;
struct TYPE_10__ {int /*<<< orphan*/  bt_mp; int /*<<< orphan*/  bt_psize; } ;
struct TYPE_9__ {scalar_t__ lower; scalar_t__ pgno; scalar_t__* linp; int /*<<< orphan*/  flags; int /*<<< orphan*/  upper; int /*<<< orphan*/  nextpg; int /*<<< orphan*/  prevpg; } ;
typedef  TYPE_1__ PAGE ;
typedef  TYPE_2__ BTREE ;

/* Variables and functions */
 scalar_t__ BTDATAOFF ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  MPOOL_DIRTY ; 
 int /*<<< orphan*/  MPOOL_PAGE_NEXT ; 
 int /*<<< orphan*/  P_BLEAF ; 
 int /*<<< orphan*/  P_INVALID ; 
 scalar_t__ P_ROOT ; 
 int RET_ERROR ; 
 int RET_SUCCESS ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpool_delete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* mpool_get (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* mpool_new (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nroot(BTREE *t)
{
	PAGE *meta, *root;
	pgno_t npg;

	if ((root = mpool_get(t->bt_mp, 1, 0)) != NULL) {
		if (root->lower == 0 &&
		    root->pgno == 0 &&
		    root->linp[0] == 0) {
			mpool_delete(t->bt_mp, root);
			errno = EINVAL;
		} else {
			mpool_put(t->bt_mp, root, 0);
			return (RET_SUCCESS);
		}
	}
	if (errno != EINVAL)		/* It's OK to not exist. */
		return (RET_ERROR);
	errno = 0;

	if ((meta = mpool_new(t->bt_mp, &npg, MPOOL_PAGE_NEXT)) == NULL)
		return (RET_ERROR);

	if ((root = mpool_new(t->bt_mp, &npg, MPOOL_PAGE_NEXT)) == NULL)
		return (RET_ERROR);

	if (npg != P_ROOT)
		return (RET_ERROR);
	root->pgno = npg;
	root->prevpg = root->nextpg = P_INVALID;
	root->lower = BTDATAOFF;
	root->upper = t->bt_psize;
	root->flags = P_BLEAF;
	memset(meta, 0, t->bt_psize);
	mpool_put(t->bt_mp, meta, MPOOL_DIRTY);
	mpool_put(t->bt_mp, root, MPOOL_DIRTY);
	return (RET_SUCCESS);
}