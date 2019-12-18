#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* name; char* usage; char* help; int /*<<< orphan*/ * func; } ;
struct TYPE_9__ {char* name; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ SL_cmd ;

/* Variables and functions */
 scalar_t__ getenv (char*) ; 
 int /*<<< orphan*/  mandoc_template (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_3__* sl_match (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 

void
sl_help (SL_cmd *cmds, int argc, char **argv)
{
    SL_cmd *c, *prev_c;

    if (getenv("SLMANDOC")) {
	mandoc_template(cmds, NULL);
	return;
    }

    if (argc == 1) {
	prev_c = NULL;
	for (c = cmds; c->name; ++c) {
	    if (c->func) {
		if(prev_c)
		    printf ("\n\t%s%s", prev_c->usage ? prev_c->usage : "",
			    prev_c->usage ? "\n" : "");
		prev_c = c;
		printf ("%s", c->name);
	    } else
		printf (", %s", c->name);
	}
	if(prev_c)
	    printf ("\n\t%s%s", prev_c->usage ? prev_c->usage : "",
		    prev_c->usage ? "\n" : "");
    } else {
	c = sl_match (cmds, argv[1], 0);
	if (c == NULL)
	    printf ("No such command: %s. "
		    "Try \"help\" for a list of all commands\n",
		    argv[1]);
	else {
	    printf ("%s\t%s\n", c->name, c->usage);
	    if(c->help && *c->help)
		printf ("%s\n", c->help);
	    if((++c)->name && c->func == NULL) {
		printf ("Synonyms:");
		while (c->name && c->func == NULL)
		    printf ("\t%s", (c++)->name);
		printf ("\n");
	    }
	}
    }
}