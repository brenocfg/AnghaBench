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
 int /*<<< orphan*/  DO ; 
 int /*<<< orphan*/  IAC ; 
 int /*<<< orphan*/  NET2ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETADD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TELOPT_TM ; 
 int flushline ; 
 int flushout ; 
 int /*<<< orphan*/  printoption (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttyflush (int) ; 

__attribute__((used)) static void
doflush()
{
    NET2ADD(IAC, DO);
    NETADD(TELOPT_TM);
    flushline = 1;
    flushout = 1;
    ttyflush(1);			/* Flush/drop output */
    /* do printoption AFTER flush, otherwise the output gets tossed... */
    printoption("SENT", DO, TELOPT_TM);
}