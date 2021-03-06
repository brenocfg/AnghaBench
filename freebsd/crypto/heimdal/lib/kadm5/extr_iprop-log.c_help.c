#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* help; int /*<<< orphan*/  (* func ) (int,char**) ;scalar_t__ name; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ SL_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  commands ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sl_help (int /*<<< orphan*/ ,int,char**) ; 
 TYPE_2__* sl_match (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (int,char**) ; 

int
help(void *opt, int argc, char **argv)
{
    if(argc == 0) {
	sl_help(commands, 1, argv - 1 /* XXX */);
    } else {
	SL_cmd *c = sl_match (commands, argv[0], 0);
 	if(c == NULL) {
	    fprintf (stderr, "No such command: %s. "
		     "Try \"help\" for a list of commands\n",
		     argv[0]);
	} else {
	    if(c->func) {
		static char shelp[] = "--help";
		char *fake[3];
		fake[0] = argv[0];
		fake[1] = shelp;
		fake[2] = NULL;
		(*c->func)(2, fake);
		fprintf(stderr, "\n");
	    }
	    if(c->help && *c->help)
		fprintf (stderr, "%s\n", c->help);
	    if((++c)->name && c->func == NULL) {
		int f = 0;
		fprintf (stderr, "Synonyms:");
		while (c->name && c->func == NULL) {
		    fprintf (stderr, "%s%s", f ? ", " : " ", (c++)->name);
		    f = 1;
		}
		fprintf (stderr, "\n");
	    }
	}
    }
    return 0;
}