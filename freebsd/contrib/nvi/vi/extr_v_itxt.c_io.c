#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  scalar_t__ recno_t ;
typedef  enum which { ____Placeholder_which } which ;
struct TYPE_14__ {int count; } ;
typedef  TYPE_1__ VICMD ;
struct TYPE_15__ {int lno; scalar_t__ cno; int /*<<< orphan*/  showmode; } ;
typedef  TYPE_2__ SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FATAL ; 
 scalar_t__ F_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * L (char*) ; 
 int /*<<< orphan*/  LOG_CORRECT ; 
 scalar_t__ OOBLNO ; 
 int O_cmd ; 
 int /*<<< orphan*/  SM_INSERT ; 
 int TXT_ADDNEWLINE ; 
 int TXT_APPENDEOL ; 
 int /*<<< orphan*/  VC_C1SET ; 
 scalar_t__ db_append (TYPE_2__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ db_get (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ db_insert (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ db_last (TYPE_2__*,scalar_t__*) ; 
 int /*<<< orphan*/  set_txt_std (TYPE_2__*,TYPE_1__*,int) ; 
 int v_txt (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
io(SCR *sp, VICMD *vp, enum which cmd)
{
	recno_t ai_line, lno;
	size_t len;
	u_int32_t flags;
	CHAR_T *p;

	flags = set_txt_std(sp, vp, TXT_ADDNEWLINE | TXT_APPENDEOL);
	sp->showmode = SM_INSERT;

	if (sp->lno == 1) {
		if (db_last(sp, &lno))
			return (1);
		if (lno != 0)
			goto insert;
		p = NULL;
		len = 0;
		ai_line = OOBLNO;
	} else {
insert:		p = L("");
		sp->cno = 0;
		LOG_CORRECT;

		if (cmd == O_cmd) {
			if (db_insert(sp, sp->lno, p, 0))
				return (1);
			if (db_get(sp, sp->lno, DBG_FATAL, &p, &len))
				return (1);
			ai_line = sp->lno + 1;
		} else {
			if (db_append(sp, 1, sp->lno, p, 0))
				return (1);
			if (db_get(sp, ++sp->lno, DBG_FATAL, &p, &len))
				return (1);
			ai_line = sp->lno - 1;
		}
	}
	return (v_txt(sp, vp, NULL, p, len,
	    0, ai_line, F_ISSET(vp, VC_C1SET) ? vp->count : 1, flags));
}