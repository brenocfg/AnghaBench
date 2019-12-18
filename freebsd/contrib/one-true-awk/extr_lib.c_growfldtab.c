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
struct Cell {int dummy; } ;
typedef  int /*<<< orphan*/  Cell ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,int) ; 
 int /*<<< orphan*/ ** fldtab ; 
 int /*<<< orphan*/  makefields (int,int) ; 
 int nfields ; 
 scalar_t__ realloc (int /*<<< orphan*/ **,size_t) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ **) ; 

void growfldtab(int n)	/* make new fields up to at least $n */
{
	int nf = 2 * nfields;
	size_t s;

	if (n > nf)
		nf = n;
	s = (nf+1) * (sizeof (struct Cell *));  /* freebsd: how much do we need? */
	if (s / sizeof(struct Cell *) - 1 == nf) /* didn't overflow */
		fldtab = (Cell **) realloc(fldtab, s);
	else					/* overflow sizeof int */
		xfree(fldtab);	/* make it null */
	if (fldtab == NULL)
		FATAL("out of space creating %d fields", nf);
	makefields(nfields+1, nf);
	nfields = nf;
}