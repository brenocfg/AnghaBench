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
struct option {char* name; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREEPTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int code ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 struct option* getoption (char*) ; 
 int /*<<< orphan*/  ttyout ; 

void
unsetoption(int argc, char *argv[])
{
	struct option *o;

	code = -1;
	if (argc == 0 || argc != 2) {
		UPRINTF("usage: %s option\n", argv[0]);
		return;
	}

	o = getoption(argv[1]);
	if (o == NULL) {
		fprintf(ttyout, "No such option `%s'.\n", argv[1]);
		return;
	}
	FREEPTR(o->value);
	fprintf(ttyout, "Unsetting `%s'.\n", o->name);
	code = 0;
}