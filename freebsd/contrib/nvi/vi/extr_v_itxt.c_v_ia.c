#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_12__ {int /*<<< orphan*/  lno; } ;
struct TYPE_13__ {int count; TYPE_1__ m_start; } ;
typedef  TYPE_2__ VICMD ;
struct TYPE_14__ {int cno; int /*<<< orphan*/  lno; int /*<<< orphan*/  showmode; } ;
typedef  TYPE_3__ SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LF_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OOBLNO ; 
 int /*<<< orphan*/  SM_APPEND ; 
 int /*<<< orphan*/  TXT_APPENDEOL ; 
 int /*<<< orphan*/  VC_C1SET ; 
 scalar_t__ db_eget (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*,int*) ; 
 int /*<<< orphan*/  set_txt_std (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int v_txt (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
v_ia(SCR *sp, VICMD *vp)
{
	size_t len;
	u_int32_t flags;
	int isempty;
	CHAR_T *p;

	flags = set_txt_std(sp, vp, 0);
	sp->showmode = SM_APPEND;
	sp->lno = vp->m_start.lno;

	/* Move the cursor one column to the right and repaint the screen. */
	if (db_eget(sp, sp->lno, &p, &len, &isempty)) {
		if (!isempty)
			return (1);
		len = 0;
		LF_SET(TXT_APPENDEOL);
	} else if (len) {
		if (len == sp->cno + 1) {
			sp->cno = len;
			LF_SET(TXT_APPENDEOL);
		} else
			++sp->cno;
	} else
		LF_SET(TXT_APPENDEOL);

	return (v_txt(sp, vp, NULL, p, len,
	    0, OOBLNO, F_ISSET(vp, VC_C1SET) ? vp->count : 1, flags));
}