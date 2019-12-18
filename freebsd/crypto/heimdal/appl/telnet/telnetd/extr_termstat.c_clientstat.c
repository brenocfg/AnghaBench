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
struct winsize {int ws_col; int ws_row; } ;

/* Variables and functions */
#define  TELOPT_NAWS 129 
#define  TELOPT_TSPEED 128 
 int /*<<< orphan*/  TIOCSWINSZ ; 
 int def_col ; 
 int def_row ; 
 int def_rspeed ; 
 int def_tspeed ; 
 int /*<<< orphan*/  init_termbuf () ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netflush () ; 
 int /*<<< orphan*/  ourpty ; 
 int /*<<< orphan*/  set_termbuf () ; 
 int /*<<< orphan*/  tty_rspeed (int) ; 
 int /*<<< orphan*/  tty_tspeed (int) ; 

void
clientstat(int code, int parm1, int parm2)
{
    /*
     * Get a copy of terminal characteristics.
     */
    init_termbuf();

    /*
     * Process request from client. code tells what it is.
     */
    switch (code) {
    case TELOPT_NAWS:
#ifdef	TIOCSWINSZ
	{
	    struct winsize ws;

	    def_col = parm1;
	    def_row = parm2;

	    /*
	     * Change window size as requested by client.
	     */

	    ws.ws_col = parm1;
	    ws.ws_row = parm2;
	    ioctl(ourpty, TIOCSWINSZ, (char *)&ws);
	}
#endif	/* TIOCSWINSZ */

    break;

    case TELOPT_TSPEED:
	{
	    def_tspeed = parm1;
	    def_rspeed = parm2;
	    /*
	     * Change terminal speed as requested by client.
	     * We set the receive speed first, so that if we can't
	     * store seperate receive and transmit speeds, the transmit
	     * speed will take precedence.
	     */
	    tty_rspeed(parm2);
	    tty_tspeed(parm1);
	    set_termbuf();

	    break;

	}  /* end of case TELOPT_TSPEED */

    default:
	/* What? */
	break;
    }  /* end of switch */

    netflush();

}