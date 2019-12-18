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
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  Cell ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,char*) ; 
 int /*<<< orphan*/ * execute (int /*<<< orphan*/ *) ; 
 char* getsval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * openfile (int,char*) ; 
 int /*<<< orphan*/  tempfree (int /*<<< orphan*/ *) ; 

FILE *redirect(int a, Node *b)	/* set up all i/o redirections */
{
	FILE *fp;
	Cell *x;
	char *fname;

	x = execute(b);
	fname = getsval(x);
	fp = openfile(a, fname);
	if (fp == NULL)
		FATAL("can't open file %s", fname);
	tempfree(x);
	return fp;
}