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
 int /*<<< orphan*/  Cookedmode () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GettingInput ; 
 int /*<<< orphan*/  SHIN ; 
 int /*<<< orphan*/  STRautomatic ; 
 int /*<<< orphan*/  STRlogout ; 
 int /*<<< orphan*/  VAR_READWRITE ; 
 int child ; 
 int do_logout ; 
 scalar_t__ editing ; 
 int /*<<< orphan*/  goodbye (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprintf (char*) ; 

__attribute__((used)) static void
auto_logout(void)
{
    xprintf("auto-logout\n");
    /* Don't leave the tty in raw mode */
    if (editing)
	(void) Cookedmode();
    xclose(SHIN);
    setcopy(STRlogout, STRautomatic, VAR_READWRITE);
    child = 1;
#ifdef TESLA
    do_logout = 1;
#endif /* TESLA */
    GettingInput = FALSE; /* make flush() work to write hist files. Huber*/
    goodbye(NULL, NULL);
}