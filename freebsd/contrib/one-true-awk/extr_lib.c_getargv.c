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
typedef  int /*<<< orphan*/  Array ;

/* Variables and functions */
 int /*<<< orphan*/  STR ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 char* getsval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookup (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setsymtab (char*,char*,double,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

char *getargv(int n)	/* get ARGV[n] */
{
	Cell *x;
	char *s, temp[50];
	extern Array *ARGVtab;

	sprintf(temp, "%d", n);
	if (lookup(temp, ARGVtab) == NULL)
		return NULL;
	x = setsymtab(temp, "", 0.0, STR, ARGVtab);
	s = getsval(x);
	   dprintf( ("getargv(%d) returns |%s|\n", n, s) );
	return s;
}