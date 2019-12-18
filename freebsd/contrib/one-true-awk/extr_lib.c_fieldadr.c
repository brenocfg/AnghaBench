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
typedef  int /*<<< orphan*/  Cell ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,int) ; 
 int /*<<< orphan*/ ** fldtab ; 
 int /*<<< orphan*/  growfldtab (int) ; 
 int nfields ; 

Cell *fieldadr(int n)	/* get nth field */
{
	if (n < 0)
		FATAL("trying to access out of range field %d", n);
	if (n > nfields)	/* fields after NF are empty */
		growfldtab(n);	/* but does not increase NF */
	return(fldtab[n]);
}