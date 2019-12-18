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
typedef  int /*<<< orphan*/  mtype_t ;
struct TYPE_7__ {scalar_t__ name; int lno; scalar_t__ cno; } ;
struct TYPE_6__ {int lno; scalar_t__ cno; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ MARK ;
typedef  TYPE_2__ LMARK ;
typedef  scalar_t__ ARG_CHAR_T ;

/* Variables and functions */
 scalar_t__ ABSMARK1 ; 
 scalar_t__ ABSMARK2 ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_NAME (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  MARK_DELETED ; 
 int /*<<< orphan*/  db_exist (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* mark_find (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
mark_get(
	SCR *sp,
	ARG_CHAR_T key,
	MARK *mp,
	mtype_t mtype)
{
	LMARK *lmp;

	if (key == ABSMARK2)
		key = ABSMARK1;

	lmp = mark_find(sp, key);
	if (lmp == NULL || lmp->name != key) {
		msgq(sp, mtype, "017|Mark %s: not set", KEY_NAME(sp, key));
		return (1);
	}
	if (F_ISSET(lmp, MARK_DELETED)) {
		msgq(sp, mtype,
		    "018|Mark %s: the line was deleted", KEY_NAME(sp, key));
		return (1);
	}

	/*
	 * !!!
	 * The absolute mark is initialized to lno 1/cno 0, and historically
	 * you could use it in an empty file.  Make such a mark always work.
	 */
	if ((lmp->lno != 1 || lmp->cno != 0) && !db_exist(sp, lmp->lno)) {
		msgq(sp, mtype,
		    "019|Mark %s: cursor position no longer exists",
		    KEY_NAME(sp, key));
		return (1);
	}
	mp->lno = lmp->lno;
	mp->cno = lmp->cno;
	return (0);
}