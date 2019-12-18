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
 int /*<<< orphan*/ ** globall (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ ** saveblk (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stderror (int) ; 
 int tglob (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  trim (int /*<<< orphan*/ **) ; 

Char **
glob_all_or_error(Char **v)
{
    int gflag;

    gflag = tglob(v);
    if (gflag) {
	v = globall(v, gflag);
	if (v == NULL)
	    stderror(ERR_NAME | ERR_NOMATCH);
    } else {
	v = saveblk(v);
	trim(v);
    }
    return v;
}