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
struct slclist {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ Ambiguous (struct slclist*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct slclist* getslc (char*) ; 
 int /*<<< orphan*/  slcstate () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
slccmd(int argc, char **argv)
{
    struct slclist *c;

    if (argc != 2) {
	fprintf(stderr,
	    "Need an argument to 'slc' command.  'slc ?' for help.\r\n");
	return 0;
    }
    c = getslc(argv[1]);
    if (c == 0) {
	fprintf(stderr, "'%s': unknown argument ('slc ?' for help).\r\n",
    				argv[1]);
	return 0;
    }
    if (Ambiguous(c)) {
	fprintf(stderr, "'%s': ambiguous argument ('slc ?' for help).\r\n",
    				argv[1]);
	return 0;
    }
    (*c->handler)(c->arg);
    slcstate();
    return 1;
}