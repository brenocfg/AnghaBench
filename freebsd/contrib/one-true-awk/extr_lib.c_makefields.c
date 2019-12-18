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
struct Cell {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  nval; } ;
typedef  TYPE_1__ Cell ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,int) ; 
 TYPE_1__ dollar1 ; 
 TYPE_1__** fldtab ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  tostring (char*) ; 

void makefields(int n1, int n2)		/* create $n1..$n2 inclusive */
{
	char temp[50];
	int i;

	for (i = n1; i <= n2; i++) {
		fldtab[i] = (Cell *) malloc(sizeof (struct Cell));
		if (fldtab[i] == NULL)
			FATAL("out of space in makefields %d", i);
		*fldtab[i] = dollar1;
		sprintf(temp, "%d", i);
		fldtab[i]->nval = tostring(temp);
	}
}