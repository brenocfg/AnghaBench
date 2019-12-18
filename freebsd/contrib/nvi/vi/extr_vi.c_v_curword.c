#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t klen; char* keyw; int /*<<< orphan*/  keywlen; } ;
typedef  TYPE_1__ VI_PRIVATE ;
struct TYPE_11__ {size_t cno; int /*<<< orphan*/  lno; } ;
typedef  TYPE_2__ SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  BINC_RETW (TYPE_2__*,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  DBG_FATAL ; 
 scalar_t__ ISSPACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMMOVE (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  M_BERR ; 
 TYPE_1__* VIP (TYPE_2__*) ; 
 scalar_t__ db_get (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ inword (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgq (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vs_refresh (TYPE_2__*,int /*<<< orphan*/ ) ; 

int
v_curword(SCR *sp)
{
	VI_PRIVATE *vip;
	size_t beg, end, len;
	int moved;
	CHAR_T *p;

	if (db_get(sp, sp->lno, DBG_FATAL, &p, &len))
		return (1);

	/*
	 * !!!
	 * Historically, tag commands skipped over any leading whitespace
	 * characters.  Make this true in general when using cursor words.
	 * If movement, getting a cursor word implies moving the cursor to
	 * its beginning.  Refresh now.
	 *
	 * !!!
	 * Find the beginning/end of the keyword.  Keywords are currently
	 * used for cursor-word searching and for tags.  Historical vi
	 * only used the word in a tag search from the cursor to the end
	 * of the word, i.e. if the cursor was on the 'b' in " abc ", the
	 * tag was "bc".  For consistency, we make cursor word searches
	 * follow the same rule.
	 */
	for (moved = 0,
	    beg = sp->cno; beg < len && ISSPACE(p[beg]); moved = 1, ++beg);
	if (beg >= len) {
		msgq(sp, M_BERR, "212|Cursor not in a word");
		return (1);
	}
	if (moved) {
		sp->cno = beg;
		(void)vs_refresh(sp, 0);
	}

	/*
	 * Find the end of the word.
	 *
	 * !!!
	 * Historically, vi accepted any non-blank as initial character
	 * when building up a tagstring.  Required by IEEE 1003.1-2001.
	 */
	for (end = beg; ++end < len && inword(p[end]););

	vip = VIP(sp);
	vip->klen = len = (end - beg);
	BINC_RETW(sp, vip->keyw, vip->keywlen, len+1);
	MEMMOVE(vip->keyw, p + beg, len);
	vip->keyw[len] = '\0';				/* XXX */
	return (0);
}