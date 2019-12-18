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
struct togglelist {char* name; char* help; char* actionexplanation; int /*<<< orphan*/ * charp; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ) ;scalar_t__* variable; } ;
struct setlist {char* name; char* help; char* actionexplanation; int /*<<< orphan*/ * charp; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ) ;scalar_t__* variable; } ;

/* Variables and functions */
 scalar_t__ Ambiguous (struct togglelist*) ; 
 struct togglelist* GETTOGGLE (char*) ; 
 struct togglelist* Setlist ; 
 int /*<<< orphan*/  _POSIX_VDISABLE ; 
 char* control (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct togglelist* getset (char*) ; 
 scalar_t__ isprefix (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  settogglehelp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
unsetcmd(int argc, char *argv[])
{
    struct setlist *ct;
    struct togglelist *c;
    char *name;

    if (argc < 2) {
	fprintf(stderr,
	    "Need an argument to 'unset' command.  'unset ?' for help.\r\n");
	return 0;
    }
    if (isprefix(argv[1], "?") || isprefix(argv[1], "help")) {
	for (ct = Setlist; ct->name; ct++)
	    printf("%-15s %s\r\n", ct->name, ct->help);
	printf("\r\n");
	settogglehelp(0);
	printf("%-15s %s\r\n", "?", "display help information");
	return 0;
    }

    argc--;
    argv++;
    while (argc--) {
	name = *argv++;
	ct = getset(name);
	if (ct == 0) {
	    c = GETTOGGLE(name);
	    if (c == 0) {
		fprintf(stderr, "'%s': unknown argument ('unset ?' for help).\r\n",
			name);
		return 0;
	    } else if (Ambiguous(c)) {
		fprintf(stderr, "'%s': ambiguous argument ('unset ?' for help).\r\n",
			name);
		return 0;
	    }
	    if (c->variable) {
		*c->variable = 0;
		if (c->actionexplanation) {
		    printf("%s %s.\r\n", *c->variable? "Will" : "Won't",
							c->actionexplanation);
		}
	    }
	    if (c->handler)
		(*c->handler)(0);
	} else if (Ambiguous(ct)) {
	    fprintf(stderr, "'%s': ambiguous argument ('unset ?' for help).\r\n",
			name);
	    return 0;
	} else if (ct->handler) {
	    (*ct->handler)(0);
	    printf("%s reset to \"%s\".\r\n", ct->name, (char *)ct->charp);
	} else {
	    *(ct->charp) = _POSIX_VDISABLE;
	    printf("%s character is '%s'.\r\n", ct->name, control(*(ct->charp)));
	}
    }
    return 1;
}