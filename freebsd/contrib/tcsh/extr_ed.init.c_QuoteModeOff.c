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
 int /*<<< orphan*/  SHTTY ; 
 scalar_t__ Tty_quote_mode ; 
 int /*<<< orphan*/  edtty ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int tty_setty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ ) ; 

void
QuoteModeOff(void)
{
    if (!Tty_quote_mode)
	return;
    Tty_quote_mode = 0;
    if (tty_setty(SHTTY, &edtty) == -1) {
#ifdef DEBUG_TTY
	xprintf("QuoteModeOff: tty_setty: %s\n", strerror(errno));
#endif /* DEBUG_TTY */
	return;
    }
    return;
}