#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  bt_mp; int /*<<< orphan*/  bt_free; } ;
struct TYPE_7__ {int /*<<< orphan*/  pgno; int /*<<< orphan*/  nextpg; int /*<<< orphan*/  prevpg; } ;
typedef  TYPE_1__ PAGE ;
typedef  TYPE_2__ BTREE ;

/* Variables and functions */
 int /*<<< orphan*/  B_METADIRTY ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPOOL_DIRTY ; 
 int /*<<< orphan*/  P_INVALID ; 
 int mpool_put (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

int
__bt_free(BTREE *t, PAGE *h)
{
	/* Insert the page at the head of the free list. */
	h->prevpg = P_INVALID;
	h->nextpg = t->bt_free;
	t->bt_free = h->pgno;
	F_SET(t, B_METADIRTY);

	/* Make sure the page gets written back. */
	return (mpool_put(t->bt_mp, h, MPOOL_DIRTY));
}