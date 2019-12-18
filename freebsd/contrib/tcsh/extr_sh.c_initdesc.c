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

/* Variables and functions */
 int /*<<< orphan*/  FOLDSTD ; 
 int /*<<< orphan*/  FSHDIAG ; 
 int /*<<< orphan*/  FSHIN ; 
 int /*<<< orphan*/  FSHOUT ; 
 scalar_t__ OLDSTD ; 
 scalar_t__ SHDIAG ; 
 int SHIN ; 
 scalar_t__ SHOUT ; 
 int /*<<< orphan*/  close_on_exec (scalar_t__,int) ; 
 void* dcopy (int,int /*<<< orphan*/ ) ; 
 scalar_t__ didcch ; 
 scalar_t__ didfds ; 
 void* isatty (scalar_t__) ; 
 void* isdiagatty ; 
 void* isoutatty ; 
 int /*<<< orphan*/  nlsclose () ; 
 int /*<<< orphan*/  nlsinit () ; 

void
initdesc(void)
{
#ifdef NLS_BUGS
#ifdef NLS_CATALOGS
    nlsclose();
#endif /* NLS_CATALOGS */
#endif /* NLS_BUGS */


    didfds = 0;			/* 0, 1, 2 aren't set up */
    (void) close_on_exec(SHIN = dcopy(0, FSHIN), 1);
    (void) close_on_exec(SHOUT = dcopy(1, FSHOUT), 1);
    (void) close_on_exec(SHDIAG = dcopy(2, FSHDIAG), 1);
    (void) close_on_exec(OLDSTD = dcopy(SHIN, FOLDSTD), 1);
#ifndef CLOSE_ON_EXEC
    didcch = 0;			/* Havent closed for child */
#endif /* CLOSE_ON_EXEC */
    if (SHDIAG >= 0)
	isdiagatty = isatty(SHDIAG);
    else
    	isdiagatty = 0;
    if (SHDIAG >= 0)
	isoutatty = isatty(SHOUT);
    else
    	isoutatty = 0;
#ifdef NLS_BUGS
#ifdef NLS_CATALOGS
    nlsinit();
#endif /* NLS_CATALOGS */
#endif /* NLS_BUGS */
}