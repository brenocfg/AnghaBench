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
 int DEFNFSDCNT ; 
 int MAXNFSDCNT ; 
 int nfsdcnt ; 
 int nfsdcnt_set ; 
 int /*<<< orphan*/  warnx (char*,int,int) ; 

__attribute__((used)) static void
set_nfsdcnt(int proposed)
{

	if (proposed < 1) {
		warnx("nfsd count too low %d; reset to %d", proposed,
		    DEFNFSDCNT);
		nfsdcnt = DEFNFSDCNT;
	} else if (proposed > MAXNFSDCNT) {
		warnx("nfsd count too high %d; truncated to %d", proposed,
		    MAXNFSDCNT);
		nfsdcnt = MAXNFSDCNT;
	} else
		nfsdcnt = proposed;
	nfsdcnt_set = 1;
}