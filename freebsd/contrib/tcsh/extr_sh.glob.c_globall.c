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
 int G_CSH ; 
 int G_GLOB ; 
 int /*<<< orphan*/  STRnoglob ; 
 scalar_t__ adrof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup ; 
 int /*<<< orphan*/  cleanup_ignore (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  cleanup_push (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** globexpand (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ ** libglob (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** saveblk (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  trim (int /*<<< orphan*/ **) ; 

Char  **
globall(Char **v, int gflg)
{
    Char  **vl, **vo;
    int noglob;

    if (!v || !v[0])
	return saveblk(v);

    noglob = adrof(STRnoglob) != 0;

    if (gflg & G_CSH)
	/*
	 * Expand back-quote, tilde and brace
	 */
	vl = vo = globexpand(v, noglob);
    else
	vl = vo = saveblk(v);

    if (!noglob && (gflg & G_GLOB)) {
	cleanup_push(vo, blk_cleanup);
	vl = libglob(vo);
	if (vl == vo)
	    cleanup_ignore(vo);
	cleanup_until(vo);
    }
    else
	trim(vl);

    return vl;
}