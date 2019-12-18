#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char mode; int /*<<< orphan*/ * fp; int /*<<< orphan*/ * fname; } ;
struct TYPE_9__ {int /*<<< orphan*/  sval; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ Cell ;
typedef  int /*<<< orphan*/  Awkfloat ;

/* Variables and functions */
 int EOF ; 
 char LE ; 
 int /*<<< orphan*/  WARNING (char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* execute (int /*<<< orphan*/ *) ; 
 int fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 TYPE_6__* files ; 
 int /*<<< orphan*/  getsval (TYPE_1__*) ; 
 TYPE_1__* gettemp () ; 
 int nfiles ; 
 int pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setfval (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tempfree (TYPE_1__*) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

Cell *closefile(Node **a, int n)
{
	Cell *x;
	int i, stat;

	x = execute(a[0]);
	getsval(x);
	stat = -1;
	for (i = 0; i < nfiles; i++) {
		if (files[i].fname && strcmp(x->sval, files[i].fname) == 0) {
			if (ferror(files[i].fp))
				WARNING( "i/o error occurred on %s", files[i].fname );
			if (files[i].mode == '|' || files[i].mode == LE)
				stat = pclose(files[i].fp);
			else
				stat = fclose(files[i].fp);
			if (stat == EOF)
				WARNING( "i/o error occurred closing %s", files[i].fname );
			if (i > 2)	/* don't do /dev/std... */
				xfree(files[i].fname);
			files[i].fname = NULL;	/* watch out for ref thru this */
			files[i].fp = NULL;
		}
	}
	tempfree(x);
	x = gettemp();
	setfval(x, (Awkfloat) stat);
	return(x);
}