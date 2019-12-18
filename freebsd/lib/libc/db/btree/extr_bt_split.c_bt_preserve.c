#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pgno_t ;
struct TYPE_7__ {int /*<<< orphan*/  bt_mp; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ PAGE ;
typedef  TYPE_2__ BTREE ;

/* Variables and functions */
 int /*<<< orphan*/  MPOOL_DIRTY ; 
 int /*<<< orphan*/  P_PRESERVE ; 
 int RET_ERROR ; 
 int RET_SUCCESS ; 
 TYPE_1__* mpool_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bt_preserve(BTREE *t, pgno_t pg)
{
	PAGE *h;

	if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
		return (RET_ERROR);
	h->flags |= P_PRESERVE;
	mpool_put(t->bt_mp, h, MPOOL_DIRTY);
	return (RET_SUCCESS);
}