#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VICMD ;
struct TYPE_2__ {size_t klen; int /*<<< orphan*/ * keyw; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  FORWARD ; 
 int /*<<< orphan*/  FREE_SPACEW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  GET_SPACE_RETW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/ * L (char*) ; 
 size_t MAX (int,int) ; 
 int /*<<< orphan*/  MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * RE_NWSTOP ; 
 int RE_NWSTOP_LEN ; 
 int /*<<< orphan*/ * RE_WSTART ; 
 int RE_WSTART_LEN ; 
 int /*<<< orphan*/ * RE_WSTOP ; 
 int RE_WSTOP_LEN ; 
 int /*<<< orphan*/  SEARCH_SET ; 
 TYPE_1__* VIP (int /*<<< orphan*/ *) ; 
 scalar_t__ inword (int /*<<< orphan*/ ) ; 
 scalar_t__ is_special (int /*<<< orphan*/ ) ; 
 int v_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
v_searchw(SCR *sp, VICMD *vp)
{
	size_t blen, len;
	int rval;
	CHAR_T *bp, *p;

	/* An upper bound for the SIZE of the RE under construction. */
	len = VIP(sp)->klen + MAX(RE_WSTART_LEN, 1)
	    + MAX(RE_WSTOP_LEN, RE_NWSTOP_LEN);
	GET_SPACE_RETW(sp, bp, blen, len);
	p = bp;

	/* Only the first character can be non-word, see v_curword. */
	if (inword(VIP(sp)->keyw[0])) {
		MEMCPY(p, RE_WSTART, RE_WSTART_LEN);
		p += RE_WSTART_LEN;
	} else if (is_special(VIP(sp)->keyw[0])) {
		MEMCPY(p, L("\\"), 1);
		p += 1;
	}

	MEMCPY(p, VIP(sp)->keyw, VIP(sp)->klen);
	p += VIP(sp)->klen;

	if (inword(p[-1])) {
		MEMCPY(p, RE_WSTOP, RE_WSTOP_LEN);
		p += RE_WSTOP_LEN;
	} else {
		/*
		 * The keyword is a single non-word character.
		 * We want it to stay the same when typing ^A several times
		 * in a row, just the way the other cases behave.
		 */
		MEMCPY(p, RE_NWSTOP, RE_NWSTOP_LEN);
		p += RE_NWSTOP_LEN;
	}

	len = p - bp;
	rval = v_search(sp, vp, bp, len, SEARCH_SET, FORWARD);

	FREE_SPACEW(sp, bp, blen);
	return (rval);
}