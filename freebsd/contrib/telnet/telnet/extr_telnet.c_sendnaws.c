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
 void* IAC ; 
 int NETROOM () ; 
 int /*<<< orphan*/  PUTSHORT (unsigned char*,long) ; 
 int /*<<< orphan*/  SB ; 
 int /*<<< orphan*/  SE ; 
 int /*<<< orphan*/  TELOPT_NAWS ; 
 scalar_t__ TerminalWindowSize (long*,long*) ; 
 scalar_t__ my_state_is_wont (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netoring ; 
 int /*<<< orphan*/  printsub (char,unsigned char*,int) ; 
 int /*<<< orphan*/  ring_supply_data (int /*<<< orphan*/ *,unsigned char*,int) ; 

void
sendnaws(void)
{
    long rows, cols;
    unsigned char tmp[16];
    unsigned char *cp;

    if (my_state_is_wont(TELOPT_NAWS))
	return;

#define	PUTSHORT(cp, x) { if ((*cp++ = ((x)>>8)&0xff) == IAC) *cp++ = IAC; \
			    if ((*cp++ = ((x))&0xff) == IAC) *cp++ = IAC; }

    if (TerminalWindowSize(&rows, &cols) == 0) {	/* Failed */
	return;
    }

    cp = tmp;

    *cp++ = IAC;
    *cp++ = SB;
    *cp++ = TELOPT_NAWS;
    PUTSHORT(cp, cols);
    PUTSHORT(cp, rows);
    *cp++ = IAC;
    *cp++ = SE;
    if (NETROOM() >= cp - tmp) {
	ring_supply_data(&netoring, tmp, cp-tmp);
	printsub('>', tmp+2, cp - tmp - 2);
    }
}