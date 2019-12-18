#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pgno_t ;
struct TYPE_9__ {int /*<<< orphan*/  bt_mp; int /*<<< orphan*/  bt_free; } ;
struct TYPE_8__ {int /*<<< orphan*/  nextpg; } ;
typedef  TYPE_1__ PAGE ;
typedef  TYPE_2__ BTREE ;

/* Variables and functions */
 int /*<<< orphan*/  B_METADIRTY ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPOOL_PAGE_NEXT ; 
 int /*<<< orphan*/  P_INVALID ; 
 TYPE_1__* mpool_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mpool_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

PAGE *
__bt_new(BTREE *t, pgno_t *npg)
{
	PAGE *h;

	if (t->bt_free != P_INVALID &&
	    (h = mpool_get(t->bt_mp, t->bt_free, 0)) != NULL) {
		*npg = t->bt_free;
		t->bt_free = h->nextpg;
		F_SET(t, B_METADIRTY);
		return (h);
	}
	return (mpool_new(t->bt_mp, npg, MPOOL_PAGE_NEXT));
}