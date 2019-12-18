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
 int /*<<< orphan*/  FATAL (char*) ; 
 int /*<<< orphan*/  cleanfld (int,int) ; 
 int /*<<< orphan*/  growfldtab (int) ; 
 int lastfld ; 
 int nfields ; 

void setlastfld(int n)	/* set lastfld cleaning fldtab cells if necessary */
{
	if (n < 0)
		FATAL("cannot set NF to a negative value");
	if (n > nfields)
		growfldtab(n);

	if (lastfld < n)
	    cleanfld(lastfld+1, n);
	else
	    cleanfld(n+1, lastfld);

	lastfld = n;
}