#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct TYPE_9__ {int /*<<< orphan*/  cno; int /*<<< orphan*/  lno; } ;
struct TYPE_8__ {int cno; } ;
struct TYPE_10__ {scalar_t__ character; int count; TYPE_2__ m_start; TYPE_1__ m_stop; TYPE_1__ m_final; } ;
typedef  TYPE_3__ VICMD ;
struct TYPE_11__ {int /*<<< orphan*/  csearchdir; scalar_t__ lastckey; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  scalar_t__ CHAR_T ;
typedef  scalar_t__ ARG_CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  FSEARCH ; 
 scalar_t__ F_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ISMOTION (TYPE_3__*) ; 
 int /*<<< orphan*/  VC_C1SET ; 
 int /*<<< orphan*/  VC_ISDOT ; 
 TYPE_5__* VIP (int /*<<< orphan*/ *) ; 
 scalar_t__ db_eget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__**,size_t*,int*) ; 
 int /*<<< orphan*/  notfound (int /*<<< orphan*/ *,scalar_t__) ; 

int
v_chF(SCR *sp, VICMD *vp)
{
	size_t len;
	u_long cnt;
	int isempty;
	ARG_CHAR_T key;
	CHAR_T *endp, *p;

	/*
	 * !!!
	 * If it's a dot command, it doesn't reset the key for which
	 * we're searching, e.g. in "df1|f2|.|;", the ';' searches
	 * for a '2'.
	 */
	key = vp->character;
	if (!F_ISSET(vp, VC_ISDOT))
		VIP(sp)->lastckey = key;
	VIP(sp)->csearchdir = FSEARCH;

	if (db_eget(sp, vp->m_start.lno, &p, &len, &isempty)) {
		if (isempty)
			goto empty;
		return (1);
	}

	if (len == 0) {
empty:		notfound(sp, key);
		return (1);
	}

	endp = p - 1;
	p += vp->m_start.cno;
	for (cnt = F_ISSET(vp, VC_C1SET) ? vp->count : 1; cnt--;) {
		while (--p > endp && *p != key);
		if (p == endp) {
			notfound(sp, key);
			return (1);
		}
	}

	vp->m_stop.cno = (p - endp) - 1;

	/*
	 * All commands move to the end of the range.  Motion commands
	 * adjust the starting point to the character before the current
	 * one.
	 */
	vp->m_final = vp->m_stop;
	if (ISMOTION(vp))
		--vp->m_start.cno;
	return (0);
}