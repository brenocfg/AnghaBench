#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* consume; } ;

/* Variables and functions */
#define  IAC 128 
 int MODE_EDIT ; 
 scalar_t__ MODE_LOCAL_CHARS (int) ; 
 int /*<<< orphan*/  NET2ADD (int const,int const) ; 
 int /*<<< orphan*/  NETADD (int) ; 
 int NETROOM () ; 
 int /*<<< orphan*/  TELOPT_BINARY ; 
 scalar_t__ TerminalSpecialChars (int) ; 
 int _POSIX_VDISABLE ; 
 int bol ; 
 int /*<<< orphan*/  command (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  crlf ; 
 int dontlecho ; 
 int echoc ; 
 int /*<<< orphan*/  echotoggle ; 
 int escape ; 
 int flushline ; 
 int globalmode ; 
 scalar_t__ kludgelinemode ; 
 int local ; 
 scalar_t__ my_want_state_is_wont (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ring_consumed (TYPE_1__*,int) ; 
 int ring_full_consecutive (TYPE_1__*) ; 
 int rlogin ; 
 int /*<<< orphan*/  setconnmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  settimer (int /*<<< orphan*/ ) ; 
 int strip (unsigned char) ; 
 int termEofChar ; 
 int termSuspChar ; 
 TYPE_1__ ttyiring ; 

__attribute__((used)) static int
telsnd(void)
{
    int tcc;
    int count;
    int returnValue = 0;
    unsigned char *tbp;

    tcc = 0;
    count = 0;
    while (NETROOM() > 2) {
	int sc;
	int c;

	if (tcc == 0) {
	    if (count) {
		ring_consumed(&ttyiring, count);
		returnValue = 1;
		count = 0;
	    }
	    tbp = ttyiring.consume;
	    tcc = ring_full_consecutive(&ttyiring);
	    if (tcc == 0) {
		break;
	    }
	}
	c = *tbp++ & 0xff, sc = strip(c), tcc--; count++;
	if (rlogin != _POSIX_VDISABLE) {
		if (bol) {
			bol = 0;
			if (sc == rlogin) {
				local = 1;
				continue;
			}
		} else if (local) {
			local = 0;
			if (sc == '.' || c == termEofChar) {
				bol = 1;
				command(0, "close\n", 6);
				continue;
			}
			if (sc == termSuspChar) {
				bol = 1;
				command(0, "z\n", 2);
				continue;
			}
			if (sc == escape) {
				command(0, tbp, tcc);
				bol = 1;
				count += tcc;
				tcc = 0;
				flushline = 1;
				break;
			}
			if (sc != rlogin) {
				++tcc;
				--tbp;
				--count;
				c = sc = rlogin;
			}
		}
		if ((sc == '\n') || (sc == '\r'))
			bol = 1;
	} else if (escape != _POSIX_VDISABLE && sc == escape) {
	    /*
	     * Double escape is a pass through of a single escape character.
	     */
	    if (tcc && strip(*tbp) == escape) {
		tbp++;
		tcc--;
		count++;
		bol = 0;
	    } else {
		command(0, (char *)tbp, tcc);
		bol = 1;
		count += tcc;
		tcc = 0;
		flushline = 1;
		break;
	    }
	} else
	    bol = 0;
#ifdef	KLUDGELINEMODE
	if (kludgelinemode && (globalmode&MODE_EDIT) && (sc == echoc)) {
	    if (tcc > 0 && strip(*tbp) == echoc) {
		tcc--; tbp++; count++;
	    } else {
		dontlecho = !dontlecho;
		settimer(echotoggle);
		setconnmode(0);
		flushline = 1;
		break;
	    }
	}
#endif
	if (MODE_LOCAL_CHARS(globalmode)) {
	    if (TerminalSpecialChars(sc) == 0) {
		bol = 1;
		break;
	    }
	}
	if (my_want_state_is_wont(TELOPT_BINARY)) {
	    switch (c) {
	    case '\n':
		    /*
		     * If we are in CRMOD mode (\r ==> \n)
		     * on our local machine, then probably
		     * a newline (unix) is CRLF (TELNET).
		     */
		if (MODE_LOCAL_CHARS(globalmode)) {
		    NETADD('\r');
		}
		NETADD('\n');
		bol = flushline = 1;
		break;
	    case '\r':
		if (!crlf) {
		    NET2ADD('\r', '\0');
		} else {
		    NET2ADD('\r', '\n');
		}
		bol = flushline = 1;
		break;
	    case IAC:
		NET2ADD(IAC, IAC);
		break;
	    default:
		NETADD(c);
		break;
	    }
	} else if (c == IAC) {
	    NET2ADD(IAC, IAC);
	} else {
	    NETADD(c);
	}
    }
    if (count)
	ring_consumed(&ttyiring, count);
    return returnValue||count;		/* Non-zero if we did anything */
}