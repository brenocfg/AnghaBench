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
struct togglelist {int* variable; char* actionexplanation; int (* handler ) (int) ;} ;

/* Variables and functions */
 scalar_t__ Ambiguous (struct togglelist*) ; 
 struct togglelist* GETTOGGLE (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (int) ; 

__attribute__((used)) static int
toggle(int argc, char *argv[])
{
    int retval = 1;
    char *name;
    struct togglelist *c;

    if (argc < 2) {
	fprintf(stderr,
	    "Need an argument to 'toggle' command.  'toggle ?' for help.\r\n");
	return 0;
    }
    argc--;
    argv++;
    while (argc--) {
	name = *argv++;
	c = GETTOGGLE(name);
	if (Ambiguous(c)) {
	    fprintf(stderr, "'%s': ambiguous argument ('toggle ?' for help).\r\n",
					name);
	    return 0;
	} else if (c == 0) {
	    fprintf(stderr, "'%s': unknown argument ('toggle ?' for help).\r\n",
					name);
	    return 0;
	} else {
	    if (c->variable) {
		*c->variable = !*c->variable;		/* invert it */
		if (c->actionexplanation) {
		    printf("%s %s.\r\n", *c->variable? "Will" : "Won't",
							c->actionexplanation);
		}
	    }
	    if (c->handler) {
		retval &= (*c->handler)(-1);
	    }
	}
    }
    return retval;
}