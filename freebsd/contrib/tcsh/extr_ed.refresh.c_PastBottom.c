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
 int /*<<< orphan*/  ClearDisp () ; 
 int /*<<< orphan*/  MoveToLine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OldvcV ; 
 int /*<<< orphan*/  flush () ; 
 int /*<<< orphan*/  putraw (char) ; 

void
PastBottom(void)
{				/* used to go to last used screen line */
    MoveToLine(OldvcV);
    (void) putraw('\r');
    (void) putraw('\n');
    ClearDisp();
    flush();
}