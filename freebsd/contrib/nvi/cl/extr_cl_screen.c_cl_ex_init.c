#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int c_lflag; int /*<<< orphan*/  c_oflag; int /*<<< orphan*/  c_iflag; } ;
struct TYPE_5__ {TYPE_2__ ex_enter; TYPE_2__ orig; int /*<<< orphan*/ * rmso; int /*<<< orphan*/ * smso; int /*<<< orphan*/ * cuu1; int /*<<< orphan*/ * el; int /*<<< orphan*/ * cup; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ CL_PRIVATE ;

/* Variables and functions */
 TYPE_1__* CLP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CL_SCR_EX_INIT ; 
 int /*<<< orphan*/  CL_STDIN_TTY ; 
 int ECHO ; 
 int ECHOCTL ; 
 int ECHOE ; 
 int ECHOK ; 
 int ECHOKE ; 
 scalar_t__ EINTR ; 
 scalar_t__ F_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int ICANON ; 
 int /*<<< orphan*/  ICRNL ; 
 int IEXTEN ; 
 int ISIG ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  ONLCR ; 
 int /*<<< orphan*/  OPOST ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int TCSADRAIN ; 
 int TCSASOFT ; 
 int /*<<< orphan*/  cl_getcap (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ tcsetattr (int /*<<< orphan*/ ,int,TYPE_2__*) ; 

__attribute__((used)) static int
cl_ex_init(SCR *sp)
{
	CL_PRIVATE *clp;

	clp = CLP(sp);

	/* If already initialized, just set the terminal modes. */
	if (F_ISSET(clp, CL_SCR_EX_INIT))
		goto fast;

	/* If not reading from a file, we're done. */
	if (!F_ISSET(clp, CL_STDIN_TTY))
		return (0);

	/* Get the ex termcap/terminfo strings. */
	(void)cl_getcap(sp, "cup", &clp->cup);
	(void)cl_getcap(sp, "smso", &clp->smso);
	(void)cl_getcap(sp, "rmso", &clp->rmso);
	(void)cl_getcap(sp, "el", &clp->el);
	(void)cl_getcap(sp, "cuu1", &clp->cuu1);

	/* Enter_standout_mode and exit_standout_mode are paired. */
	if (clp->smso == NULL || clp->rmso == NULL) {
		if (clp->smso != NULL) {
			free(clp->smso);
			clp->smso = NULL;
		}
		if (clp->rmso != NULL) {
			free(clp->rmso);
			clp->rmso = NULL;
		}
	}

	/*
	 * Turn on canonical mode, with normal input and output processing.
	 * Start with the original terminal settings as the user probably
	 * had them (including any local extensions) set correctly for the
	 * current terminal.
	 *
	 * !!!
	 * We can't get everything that we need portably; for example, ONLCR,
	 * mapping <newline> to <carriage-return> on output isn't required
	 * by POSIX 1003.1b-1993.  If this turns out to be a problem, then
	 * we'll either have to play some games on the mapping, or we'll have
	 * to make all ex printf's output \r\n instead of \n.
	 */
	clp->ex_enter = clp->orig;
	clp->ex_enter.c_lflag  |= ECHO | ECHOE | ECHOK | ICANON | IEXTEN | ISIG;
#ifdef ECHOCTL
	clp->ex_enter.c_lflag |= ECHOCTL;
#endif
#ifdef ECHOKE
	clp->ex_enter.c_lflag |= ECHOKE;
#endif
	clp->ex_enter.c_iflag |= ICRNL;
	clp->ex_enter.c_oflag |= OPOST;
#ifdef ONLCR
	clp->ex_enter.c_oflag |= ONLCR;
#endif

fast:	if (tcsetattr(STDIN_FILENO, TCSADRAIN | TCSASOFT, &clp->ex_enter)) {
		if (errno == EINTR)
			goto fast;
		msgq(sp, M_SYSERR, "tcsetattr");
		return (1);
	}
	return (0);
}