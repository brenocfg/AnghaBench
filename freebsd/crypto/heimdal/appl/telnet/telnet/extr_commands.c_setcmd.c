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
struct togglelist {char* name; char* help; int* variable; char* actionexplanation; scalar_t__* charp; int /*<<< orphan*/  (* handler ) (char*) ;} ;
struct setlist {char* name; char* help; int* variable; char* actionexplanation; scalar_t__* charp; int /*<<< orphan*/  (* handler ) (char*) ;} ;
typedef  scalar_t__ cc_t ;

/* Variables and functions */
 scalar_t__ Ambiguous (struct togglelist*) ; 
 struct togglelist* GETTOGGLE (char*) ; 
 struct togglelist* Setlist ; 
 int _POSIX_VDISABLE ; 
 char* control (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 struct togglelist* getset (char*) ; 
 scalar_t__ isprefix (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  settogglehelp (int) ; 
 int /*<<< orphan*/  slc_check () ; 
 int special (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (char*) ; 

__attribute__((used)) static int
setcmd(int argc, char *argv[])
{
    int value;
    struct setlist *ct;
    struct togglelist *c;

    if (argc < 2 || argc > 3) {
	printf("Format is 'set Name Value'\r\n'set ?' for help.\r\n");
	return 0;
    }
    if ((argc == 2) && (isprefix(argv[1], "?") || isprefix(argv[1], "help"))) {
	for (ct = Setlist; ct->name; ct++)
	    printf("%-15s %s\r\n", ct->name, ct->help);
	printf("\r\n");
	settogglehelp(1);
	printf("%-15s %s\r\n", "?", "display help information");
	return 0;
    }

    ct = getset(argv[1]);
    if (ct == 0) {
	c = GETTOGGLE(argv[1]);
	if (c == 0) {
	    fprintf(stderr, "'%s': unknown argument ('set ?' for help).\r\n",
			argv[1]);
	    return 0;
	} else if (Ambiguous(c)) {
	    fprintf(stderr, "'%s': ambiguous argument ('set ?' for help).\r\n",
			argv[1]);
	    return 0;
	}
	if (c->variable) {
	    if ((argc == 2) || (strcmp("on", argv[2]) == 0))
		*c->variable = 1;
	    else if (strcmp("off", argv[2]) == 0)
		*c->variable = 0;
	    else {
		printf("Format is 'set togglename [on|off]'\r\n'set ?' for help.\r\n");
		return 0;
	    }
	    if (c->actionexplanation) {
		printf("%s %s.\r\n", *c->variable? "Will" : "Won't",
							c->actionexplanation);
	    }
	}
	if (c->handler)
	    (*c->handler)(1);
    } else if (argc != 3) {
	printf("Format is 'set Name Value'\r\n'set ?' for help.\r\n");
	return 0;
    } else if (Ambiguous(ct)) {
	fprintf(stderr, "'%s': ambiguous argument ('set ?' for help).\r\n",
			argv[1]);
	return 0;
    } else if (ct->handler) {
	(*ct->handler)(argv[2]);
	printf("%s set to \"%s\".\r\n", ct->name, (char *)ct->charp);
    } else {
	if (strcmp("off", argv[2])) {
	    value = special(argv[2]);
	} else {
	    value = _POSIX_VDISABLE;
	}
	*(ct->charp) = (cc_t)value;
	printf("%s character is '%s'.\r\n", ct->name, control(*(ct->charp)));
    }
    slc_check();
    return 1;
}