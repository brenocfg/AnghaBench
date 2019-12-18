#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int ERR_NAME ; 
 int ERR_NOMATCH ; 
 int G_CSH ; 
 int G_GLOB ; 
 int G_NONE ; 
 int /*<<< orphan*/ * STRNULL ; 
 int /*<<< orphan*/  STRnoglob ; 
 int /*<<< orphan*/ * Strsave (int /*<<< orphan*/ *) ; 
 scalar_t__ adrof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup ; 
 int /*<<< orphan*/  cleanup_ignore (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  cleanup_push (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** globexpand (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ * handleone (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ ** libglob (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  setname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  short2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderror (int) ; 
 int /*<<< orphan*/ * strip (int /*<<< orphan*/ *) ; 
 int tglob (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ **) ; 

Char   *
globone(Char *str, int action)
{
    Char   *v[2], **vl, **vo;
    int gflg, noglob;

    noglob = adrof(STRnoglob) != 0;
    v[0] = str;
    v[1] = 0;
    gflg = tglob(v);
    if (gflg == G_NONE)
	return (strip(Strsave(str)));

    if (gflg & G_CSH) {
	/*
	 * Expand back-quote, tilde and brace
	 */
	vo = globexpand(v, noglob);
	if (noglob || (gflg & G_GLOB) == 0) {
	    vl = vo;
	    goto result;
	}
	cleanup_push(vo, blk_cleanup);
    }
    else if (noglob || (gflg & G_GLOB) == 0)
	return (strip(Strsave(str)));
    else
	vo = v;

    vl = libglob(vo);
    if (gflg & G_CSH) {
    	if (vl != vo)
	    cleanup_until(vo);
	else
	    cleanup_ignore(vo);
    }
    if (vl == NULL) {
	setname(short2str(str));
	stderror(ERR_NAME | ERR_NOMATCH);
    }
 result:
    if (vl && vl[0] == NULL) {
	xfree(vl);
	return (Strsave(STRNULL));
    }
    if (vl && vl[1]) 
	return (handleone(str, vl, action));
    else {
	str = strip(*vl);
	xfree(vl);
	return (str);
    }
}