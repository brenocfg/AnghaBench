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
 int /*<<< orphan*/  IAC ; 
 int /*<<< orphan*/  KLUDGE_LINEMODE ; 
#define  LM_MODE 131 
 int MODE_ACK ; 
 int MODE_EDIT ; 
 int MODE_LIT_ECHO ; 
 int MODE_MASK ; 
 int MODE_SOFT_TAB ; 
 int MODE_TRAPSIG ; 
 int /*<<< orphan*/  REAL_LINEMODE ; 
 int /*<<< orphan*/  SB ; 
 int /*<<< orphan*/  SE ; 
 int /*<<< orphan*/  TELOPT_ECHO ; 
#define  TELOPT_LINEMODE 130 
#define  TELOPT_NAWS 129 
#define  TELOPT_TSPEED 128 
 int /*<<< orphan*/  TIOCSWINSZ ; 
 int WILL ; 
 int /*<<< orphan*/  alwayslinemode ; 
 int def_col ; 
 int def_row ; 
 int def_rspeed ; 
 int def_tspeed ; 
 int editmode ; 
 int /*<<< orphan*/  init_termbuf () ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int linemode ; 
 int /*<<< orphan*/  lmodetype ; 
 int /*<<< orphan*/  localstat () ; 
 int /*<<< orphan*/  netflush () ; 
 int /*<<< orphan*/  output_data (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pty ; 
 int /*<<< orphan*/  send_will (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_termbuf () ; 
 int /*<<< orphan*/  terminit () ; 
 int /*<<< orphan*/  tty_isediting () ; 
 int /*<<< orphan*/  tty_islitecho () ; 
 int /*<<< orphan*/  tty_issofttab () ; 
 int /*<<< orphan*/  tty_istrapsig () ; 
 int /*<<< orphan*/  tty_rspeed (int) ; 
 int /*<<< orphan*/  tty_setedit (int) ; 
 int /*<<< orphan*/  tty_setlinemode (int) ; 
 int /*<<< orphan*/  tty_setlitecho (int) ; 
 int /*<<< orphan*/  tty_setsig (int) ; 
 int /*<<< orphan*/  tty_setsofttab (int) ; 
 int /*<<< orphan*/  tty_tspeed (int) ; 
 int useeditmode ; 
 int uselinemode ; 

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
#ifdef	LINEMODE
	case TELOPT_LINEMODE:
		/*
		 * Don't do anything unless client is asking us to change
		 * modes.
		 */
		uselinemode = (parm1 == WILL);
		if (uselinemode != linemode) {
# ifdef	KLUDGELINEMODE
			/*
			 * If using kludge linemode, make sure that
			 * we can do what the client asks.
			 * We can not turn off linemode if alwayslinemode
			 * and the ICANON bit is set.
			 */
			if (lmodetype == KLUDGE_LINEMODE) {
				if (alwayslinemode && tty_isediting()) {
					uselinemode = 1;
				}
			}

			/*
			 * Quit now if we can't do it.
			 */
			if (uselinemode == linemode)
				return;

			/*
			 * If using real linemode and linemode is being
			 * turned on, send along the edit mode mask.
			 */
			if (lmodetype == REAL_LINEMODE && uselinemode)
# else	/* KLUDGELINEMODE */
			if (uselinemode)
# endif	/* KLUDGELINEMODE */
			{
				useeditmode = 0;
				if (tty_isediting())
					useeditmode |= MODE_EDIT;
				if (tty_istrapsig())
					useeditmode |= MODE_TRAPSIG;
				if (tty_issofttab())
					useeditmode |= MODE_SOFT_TAB;
				if (tty_islitecho())
					useeditmode |= MODE_LIT_ECHO;
				output_data("%c%c%c%c%c%c%c", IAC,
					SB, TELOPT_LINEMODE, LM_MODE,
							useeditmode, IAC, SE);
				editmode = useeditmode;
			}


			tty_setlinemode(uselinemode);

			linemode = uselinemode;

			if (!linemode)
				send_will(TELOPT_ECHO, 1);
		}
		break;

	case LM_MODE:
	    {
		int ack, changed;

		/*
		 * Client has sent along a mode mask.  If it agrees with
		 * what we are currently doing, ignore it; if not, it could
		 * be viewed as a request to change.  Note that the server
		 * will change to the modes in an ack if it is different from
		 * what we currently have, but we will not ack the ack.
		 */
		 useeditmode &= MODE_MASK;
		 ack = (useeditmode & MODE_ACK);
		 useeditmode &= ~MODE_ACK;

		 if ((changed = (useeditmode ^ editmode))) {
			/*
			 * This check is for a timing problem.  If the
			 * state of the tty has changed (due to the user
			 * application) we need to process that info
			 * before we write in the state contained in the
			 * ack!!!  This gets out the new MODE request,
			 * and when the ack to that command comes back
			 * we'll set it and be in the right mode.
			 */
			if (ack)
				localstat();
			if (changed & MODE_EDIT)
				tty_setedit(useeditmode & MODE_EDIT);

			if (changed & MODE_TRAPSIG)
				tty_setsig(useeditmode & MODE_TRAPSIG);

			if (changed & MODE_SOFT_TAB)
				tty_setsofttab(useeditmode & MODE_SOFT_TAB);

			if (changed & MODE_LIT_ECHO)
				tty_setlitecho(useeditmode & MODE_LIT_ECHO);

			set_termbuf();

 			if (!ack) {
				output_data("%c%c%c%c%c%c%c", IAC,
					SB, TELOPT_LINEMODE, LM_MODE,
 					useeditmode|MODE_ACK,
 					IAC, SE);
 			}

			editmode = useeditmode;
		}

		break;

	    }  /* end of case LM_MODE */
#endif	/* LINEMODE */

	case TELOPT_NAWS:
#ifdef	TIOCSWINSZ
	    {
		struct winsize ws;

		def_col = parm1;
		def_row = parm2;
#ifdef	LINEMODE
		/*
		 * Defer changing window size until after terminal is
		 * initialized.
		 */
		if (terminit() == 0)
			return;
#endif	/* LINEMODE */

		/*
		 * Change window size as requested by client.
		 */

		ws.ws_col = parm1;
		ws.ws_row = parm2;
		(void) ioctl(pty, TIOCSWINSZ, (char *)&ws);
	    }
#endif	/* TIOCSWINSZ */

		break;

	case TELOPT_TSPEED:
	    {
		def_tspeed = parm1;
		def_rspeed = parm2;
#ifdef	LINEMODE
		/*
		 * Defer changing the terminal speed.
		 */
		if (terminit() == 0)
			return;
#endif	/* LINEMODE */
		/*
		 * Change terminal speed as requested by client.
		 * We set the receive speed first, so that if we can't
		 * store separate receive and transmit speeds, the transmit
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