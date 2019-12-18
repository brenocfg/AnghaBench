#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int c_flags; char* c_name; int /*<<< orphan*/  (* c_init ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int CMD_ERROR ; 
 int CMD_OK ; 
 int C_ACTIVEIN ; 
 int C_ACTIVEOUT ; 
 int C_PRESENTIN ; 
 int C_PRESENTOUT ; 
 int cons_find (char*) ; 
 TYPE_1__** consoles ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strdup (char const*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cons_change(const char *string)
{
    int		cons, active;
    char	*curpos, *dup, *next;

    /* Disable all consoles */
    for (cons = 0; consoles[cons] != NULL; cons++) {
	consoles[cons]->c_flags &= ~(C_ACTIVEIN | C_ACTIVEOUT);
    }

    /* Enable selected consoles */
    dup = next = strdup(string);
    active = 0;
    while (next != NULL) {
	curpos = strsep(&next, " ,");
	if (*curpos == '\0')
		continue;
	cons = cons_find(curpos);
	if (cons >= 0) {
	    consoles[cons]->c_flags |= C_ACTIVEIN | C_ACTIVEOUT;
	    consoles[cons]->c_init(0);
	    if ((consoles[cons]->c_flags & (C_PRESENTIN | C_PRESENTOUT)) ==
		(C_PRESENTIN | C_PRESENTOUT)) {
		active++;
		continue;
	    }

	    if (active != 0) {
		/* If no consoles have initialised we wouldn't see this. */
		printf("console %s failed to initialize\n", consoles[cons]->c_name);
	    }
	}
    }

    free(dup);

    if (active == 0) {
	/* All requested consoles failed to initialise, try to recover. */
	for (cons = 0; consoles[cons] != NULL; cons++) {
	    consoles[cons]->c_flags |= C_ACTIVEIN | C_ACTIVEOUT;
	    consoles[cons]->c_init(0);
	    if ((consoles[cons]->c_flags &
		(C_PRESENTIN | C_PRESENTOUT)) ==
		(C_PRESENTIN | C_PRESENTOUT))
		active++;
	}

	if (active == 0)
	    return (CMD_ERROR); /* Recovery failed. */
    }

    return (CMD_OK);
}