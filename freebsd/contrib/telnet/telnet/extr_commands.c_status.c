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

/* Variables and functions */
 int MODE_ECHO ; 
 int MODE_EDIT ; 
 int MODE_FLOW ; 
 int MODE_TRAPSIG ; 
 int /*<<< orphan*/  TELOPT_LFLOW ; 
 int /*<<< orphan*/  TELOPT_LINEMODE ; 
 int /*<<< orphan*/  TELOPT_SGA ; 
 scalar_t__ connected ; 
 char* control (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encrypt_display () ; 
 int /*<<< orphan*/  escape ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int getconnmode () ; 
 char* hostname ; 
 scalar_t__ kludgelinemode ; 
 scalar_t__ localchars ; 
 scalar_t__ my_want_state_is_dont (int /*<<< orphan*/ ) ; 
 scalar_t__ my_want_state_is_will (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  slcstate () ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
status(int argc, char *argv[])
{
    if (connected) {
	printf("Connected to %s.\n", hostname);
	if ((argc < 2) || strcmp(argv[1], "notmuch")) {
	    int mode = getconnmode();

	    if (my_want_state_is_will(TELOPT_LINEMODE)) {
		printf("Operating with LINEMODE option\n");
		printf("%s line editing\n", (mode&MODE_EDIT) ? "Local" : "No");
		printf("%s catching of signals\n",
					(mode&MODE_TRAPSIG) ? "Local" : "No");
		slcstate();
#ifdef	KLUDGELINEMODE
	    } else if (kludgelinemode && my_want_state_is_dont(TELOPT_SGA)) {
		printf("Operating in obsolete linemode\n");
#endif
	    } else {
		printf("Operating in single character mode\n");
		if (localchars)
		    printf("Catching signals locally\n");
	    }
	    printf("%s character echo\n", (mode&MODE_ECHO) ? "Local" : "Remote");
	    if (my_want_state_is_will(TELOPT_LFLOW))
		printf("%s flow control\n", (mode&MODE_FLOW) ? "Local" : "No");
#ifdef	ENCRYPTION
	    encrypt_display();
#endif	/* ENCRYPTION */
	}
    } else {
	printf("No connection.\n");
    }
    printf("Escape character is '%s'.\n", control(escape));
    (void) fflush(stdout);
    return 1;
}