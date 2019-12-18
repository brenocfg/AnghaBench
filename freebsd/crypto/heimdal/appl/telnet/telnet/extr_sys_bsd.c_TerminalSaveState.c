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
 void* CONTROL (char) ; 
 int /*<<< orphan*/  new_tc ; 
 int /*<<< orphan*/  old_tc ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* termAytChar ; 
 void* termFlushChar ; 
 void* termLiteralNextChar ; 
 void* termRprntChar ; 
 void* termStartChar ; 
 void* termStopChar ; 
 void* termWerasChar ; 

void
TerminalSaveState(void)
{
    tcgetattr(0, &old_tc);

    new_tc = old_tc;

#ifndef	VDISCARD
    termFlushChar = CONTROL('O');
#endif
#ifndef	VWERASE
    termWerasChar = CONTROL('W');
#endif
#ifndef	VREPRINT
    termRprntChar = CONTROL('R');
#endif
#ifndef	VLNEXT
    termLiteralNextChar = CONTROL('V');
#endif
#ifndef	VSTART
    termStartChar = CONTROL('Q');
#endif
#ifndef	VSTOP
    termStopChar = CONTROL('S');
#endif
#ifndef	VSTATUS
    termAytChar = CONTROL('T');
#endif
}