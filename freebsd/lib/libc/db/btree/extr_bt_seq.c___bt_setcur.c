#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  pgno_t ;
struct TYPE_7__ {int /*<<< orphan*/  index; int /*<<< orphan*/  pgno; } ;
struct TYPE_8__ {int /*<<< orphan*/ * data; scalar_t__ size; } ;
struct TYPE_10__ {TYPE_1__ pg; TYPE_2__ key; } ;
struct TYPE_9__ {TYPE_5__ bt_cursor; } ;
typedef  TYPE_3__ BTREE ;

/* Variables and functions */
 int CURS_ACQUIRE ; 
 int CURS_AFTER ; 
 int CURS_BEFORE ; 
 int /*<<< orphan*/  CURS_INIT ; 
 int /*<<< orphan*/  F_CLR (TYPE_5__*,int) ; 
 int /*<<< orphan*/  F_SET (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
__bt_setcur(BTREE *t, pgno_t pgno, u_int idx)
{
	/* Lose any already deleted key. */
	if (t->bt_cursor.key.data != NULL) {
		free(t->bt_cursor.key.data);
		t->bt_cursor.key.size = 0;
		t->bt_cursor.key.data = NULL;
	}
	F_CLR(&t->bt_cursor, CURS_ACQUIRE | CURS_AFTER | CURS_BEFORE);

	/* Update the cursor. */
	t->bt_cursor.pg.pgno = pgno;
	t->bt_cursor.pg.index = idx;
	F_SET(&t->bt_cursor, CURS_INIT);
}