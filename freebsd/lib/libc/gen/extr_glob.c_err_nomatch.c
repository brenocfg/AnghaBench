#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct glob_limit {int dummy; } ;
struct TYPE_4__ {int gl_flags; } ;
typedef  TYPE_1__ glob_t ;

/* Variables and functions */
 int GLOB_MAGCHAR ; 
 int GLOB_NOCHECK ; 
 int GLOB_NOMAGIC ; 
 int GLOB_NOMATCH ; 
 int globextend (int /*<<< orphan*/ *,TYPE_1__*,struct glob_limit*,char const*) ; 

__attribute__((used)) static int
err_nomatch(glob_t *pglob, struct glob_limit *limit, const char *origpat) {
	/*
	 * If there was no match we are going to append the origpat
	 * if GLOB_NOCHECK was specified or if GLOB_NOMAGIC was specified
	 * and the origpat did not contain any magic characters
	 * GLOB_NOMAGIC is there just for compatibility with csh.
	 */
	if ((pglob->gl_flags & GLOB_NOCHECK) ||
	    ((pglob->gl_flags & GLOB_NOMAGIC) &&
	    !(pglob->gl_flags & GLOB_MAGCHAR)))
		return (globextend(NULL, pglob, limit, origpat));
	return (GLOB_NOMATCH);
}