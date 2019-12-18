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
typedef  int /*<<< orphan*/  Awkfloat ;

/* Variables and functions */
 int /*<<< orphan*/  cleanfld (int,int) ; 
 int /*<<< orphan*/  growfldtab (int) ; 
 int lastfld ; 
 int nfields ; 
 int /*<<< orphan*/  nfloc ; 
 int /*<<< orphan*/  setfval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void newfld(int n)	/* add field n after end of existing lastfld */
{
	if (n > nfields)
		growfldtab(n);
	cleanfld(lastfld+1, n);
	lastfld = n;
	setfval(nfloc, (Awkfloat) n);
}