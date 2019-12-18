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
 int /*<<< orphan*/  MODE_LOCAL_CHARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TELOPT_LINEMODE ; 
 int /*<<< orphan*/  globalmode ; 
 int /*<<< orphan*/  intp () ; 
 scalar_t__ kludgelinemode ; 
 scalar_t__ my_want_state_is_will (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sendabort () ; 
 int /*<<< orphan*/  sendbrk () ; 
 int /*<<< orphan*/  sendeof () ; 
 int /*<<< orphan*/  sendsusp () ; 
 int termEofChar ; 
 int termEraseChar ; 
 int termFlushChar ; 
 int termIntChar ; 
 int termKillChar ; 
 int termQuitChar ; 
 int termSuspChar ; 
 int /*<<< orphan*/  xmitAO () ; 
 int /*<<< orphan*/  xmitEC () ; 
 int /*<<< orphan*/  xmitEL () ; 

int
TerminalSpecialChars(int c)
{
    if (c == termIntChar) {
	intp();
	return 0;
    } else if (c == termQuitChar) {
#ifdef	KLUDGELINEMODE
	if (kludgelinemode)
	    sendbrk();
	else
#endif
	    sendabort();
	return 0;
    } else if (c == termEofChar) {
	if (my_want_state_is_will(TELOPT_LINEMODE)) {
	    sendeof();
	    return 0;
	}
	return 1;
    } else if (c == termSuspChar) {
	sendsusp();
	return(0);
    } else if (c == termFlushChar) {
	xmitAO();		/* Transmit Abort Output */
	return 0;
    } else if (!MODE_LOCAL_CHARS(globalmode)) {
	if (c == termKillChar) {
	    xmitEL();
	    return 0;
	} else if (c == termEraseChar) {
	    xmitEC();		/* Transmit Erase Character */
	    return 0;
	}
    }
    return 1;
}