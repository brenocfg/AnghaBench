#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct timeval {int dummy; } ;
struct termios {int c_iflag; int /*<<< orphan*/  c_lflag; } ;
typedef  int /*<<< orphan*/  input_t ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_13__ {char* c_cc; } ;
struct TYPE_14__ {int eof_count; TYPE_2__ orig; TYPE_1__* script; struct termios vi_enter; struct TYPE_14__* gp; } ;
struct TYPE_12__ {int sh_master; } ;
typedef  TYPE_3__ SCR ;
typedef  TYPE_3__ GS ;
typedef  TYPE_3__ CL_PRIVATE ;

/* Variables and functions */
 TYPE_3__* CLP (TYPE_3__*) ; 
 int /*<<< orphan*/  CL_STDIN_TTY ; 
 int EC_QUOTED ; 
 int EC_RAW ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ F_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_SCRWIN ; 
 int /*<<< orphan*/  INP_EOF ; 
 int /*<<< orphan*/  INP_ERR ; 
 int /*<<< orphan*/  INP_INTR ; 
 int /*<<< orphan*/  INP_OK ; 
 int /*<<< orphan*/  INP_TIMEOUT ; 
 int /*<<< orphan*/  ISIG ; 
 int IXOFF ; 
 int IXON ; 
 scalar_t__ LF_ISSET (int) ; 
 int /*<<< orphan*/  M_SYSERR ; 
 size_t ONE_FOR_EOF ; 
 int /*<<< orphan*/  SC_EX ; 
 int /*<<< orphan*/  SC_SCRIPT ; 
 int STDIN_FILENO ; 
 int TCSADRAIN ; 
 int TCSASOFT ; 
 size_t VEOF ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  msgq (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int read (int,char*,size_t) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ sscr_input (TYPE_3__*) ; 
 int /*<<< orphan*/  tcgetattr (int,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int,int,struct termios*) ; 

__attribute__((used)) static input_t
cl_read(SCR *sp, u_int32_t flags, char *bp, size_t blen, int *nrp,
    struct timeval *tp)
{
	struct termios term1, term2;
	CL_PRIVATE *clp;
	GS *gp;
	fd_set rdfd;
	input_t rval;
	int maxfd, nr, term_reset;

	gp = sp->gp;
	clp = CLP(sp);
	term_reset = 0;

	/*
	 * 1: A read from a file or a pipe.  In this case, the reads
	 *    never timeout regardless.  This means that we can hang
	 *    when trying to complete a map, but we're going to hang
	 *    on the next read anyway.
	 */
	if (!F_ISSET(clp, CL_STDIN_TTY)) {
		switch (nr = read(STDIN_FILENO, bp, blen)) {
		case 0:
			return (INP_EOF);
		case -1:
			goto err;
		default:
			*nrp = nr;
			return (INP_OK);
		}
		/* NOTREACHED */
	}

	/*
	 * 2: A read with an associated timeout, e.g., trying to complete
	 *    a map sequence.  If input exists, we fall into #3.
	 */
	if (tp != NULL) {
		FD_ZERO(&rdfd);
		FD_SET(STDIN_FILENO, &rdfd);
		switch (select(STDIN_FILENO + 1, &rdfd, NULL, NULL, tp)) {
		case 0:
			return (INP_TIMEOUT);
		case -1:
			goto err;
		default:
			break;
		}
	}
	
	/*
	 * The user can enter a key in the editor to quote a character.  If we
	 * get here and the next key is supposed to be quoted, do what we can.
	 * Reset the tty so that the user can enter a ^C, ^Q, ^S.  There's an
	 * obvious race here, when the key has already been entered, but there's
	 * nothing that we can do to fix that problem.
	 *
	 * The editor can ask for the next literal character even thought it's
	 * generally running in line-at-a-time mode.  Do what we can.
	 */
	if (LF_ISSET(EC_QUOTED | EC_RAW) && !tcgetattr(STDIN_FILENO, &term1)) {
		term_reset = 1;
		if (LF_ISSET(EC_QUOTED)) {
			term2 = term1;
			term2.c_lflag &= ~ISIG;
			term2.c_iflag &= ~(IXON | IXOFF);
			(void)tcsetattr(STDIN_FILENO,
			    TCSASOFT | TCSADRAIN, &term2);
		} else
			(void)tcsetattr(STDIN_FILENO,
			    TCSASOFT | TCSADRAIN, &clp->vi_enter);
	}

	/*
	 * 3: Wait for input.
	 *
	 * Select on the command input and scripting window file descriptors.
	 * It's ugly that we wait on scripting file descriptors here, but it's
	 * the only way to keep from locking out scripting windows.
	 */
	if (F_ISSET(gp, G_SCRWIN)) {
loop:		FD_ZERO(&rdfd);
		FD_SET(STDIN_FILENO, &rdfd);
		maxfd = STDIN_FILENO;
		if (F_ISSET(sp, SC_SCRIPT)) {
			FD_SET(sp->script->sh_master, &rdfd);
			if (sp->script->sh_master > maxfd)
				maxfd = sp->script->sh_master;
		}
		switch (select(maxfd + 1, &rdfd, NULL, NULL, NULL)) {
		case 0:
			abort();
		case -1:
			goto err;
		default:
			break;
		}
		if (!FD_ISSET(STDIN_FILENO, &rdfd)) {
			if (sscr_input(sp))
				return (INP_ERR);
			goto loop;
		}
	}

	/*
	 * 4: Read the input.
	 *
	 * !!!
	 * What's going on here is some scary stuff.  Ex runs the terminal in
	 * canonical mode.  So, the <newline> character terminating a line of
	 * input is returned in the buffer, but a trailing <EOF> character is
	 * not similarly included.  As ex uses 0<EOF> and ^<EOF> as autoindent
	 * commands, it has to see the trailing <EOF> characters to determine
	 * the difference between the user entering "0ab" and "0<EOF>ab".  We
	 * leave an extra slot in the buffer, so that we can add a trailing
	 * <EOF> character if the buffer isn't terminated by a <newline>.  We
	 * lose if the buffer is too small for the line and exactly N characters
	 * are entered followed by an <EOF> character.
	 */
#define	ONE_FOR_EOF	1
	switch (nr = read(STDIN_FILENO, bp, blen - ONE_FOR_EOF)) {
	case  0:				/* EOF. */
		/*
		 * ^D in canonical mode returns a read of 0, i.e. EOF.  EOF is
		 * a valid command, but we don't want to loop forever because
		 * the terminal driver is returning EOF because the user has
		 * disconnected. The editor will almost certainly try to write
		 * something before this fires, which should kill us, but You
		 * Never Know.
		 */
		if (++clp->eof_count < 50) {
			bp[0] = clp->orig.c_cc[VEOF];
			*nrp = 1;
			rval = INP_OK;

		} else
			rval = INP_EOF;
		break;
	case -1:				/* Error or interrupt. */
err:		if (errno == EINTR)
			rval = INP_INTR;
		else {
			rval = INP_ERR;
			msgq(sp, M_SYSERR, "input");
		}
		break;
	default:				/* Input characters. */
		if (F_ISSET(sp, SC_EX) && bp[nr - 1] != '\n')
			bp[nr++] = clp->orig.c_cc[VEOF];
		*nrp = nr;
		clp->eof_count = 0;
		rval = INP_OK;
		break;
	}

	/* Restore the terminal state if it was modified. */
	if (term_reset)
		(void)tcsetattr(STDIN_FILENO, TCSASOFT | TCSADRAIN, &term1);
	return (rval);
}