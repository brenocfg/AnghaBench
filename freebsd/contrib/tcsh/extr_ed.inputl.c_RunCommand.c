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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  ClearDisp () ; 
 int /*<<< orphan*/  ClearLines () ; 
 int /*<<< orphan*/  Cookedmode () ; 
 int GettingInput ; 
 scalar_t__ NeedsRedraw ; 
 int /*<<< orphan*/  Rawmode () ; 
 int /*<<< orphan*/  Refresh () ; 
 int /*<<< orphan*/  doeval1 (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  xputchar (char) ; 

__attribute__((used)) static void
RunCommand(Char *str)
{
    Char *cmd[2];

    xputchar('\n');	/* Start on a clean line */

    cmd[0] = str;
    cmd[1] = NULL;

    (void) Cookedmode();
    GettingInput = 0;

    doeval1(cmd);

    (void) Rawmode();
    GettingInput = 1;

    ClearLines();
    ClearDisp();
    NeedsRedraw = 0;
    Refresh();
}