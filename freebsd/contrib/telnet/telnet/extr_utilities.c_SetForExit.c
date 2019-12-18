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
 int /*<<< orphan*/  EmptyTerminal () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netiring ; 
 scalar_t__ ring_full_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setcommandmode () ; 
 int /*<<< orphan*/  setconnmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  telrcv () ; 

__attribute__((used)) static void
SetForExit(void)
{
    setconnmode(0);
    do {
	(void)telrcv();			/* Process any incoming data */
	EmptyTerminal();
    } while (ring_full_count(&netiring));	/* While there is any */
    setcommandmode();
    fflush(stdout);
    fflush(stderr);
    setconnmode(0);
    EmptyTerminal();			/* Flush the path to the tty */
    setcommandmode();
}