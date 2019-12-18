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
struct termios {int* c_cc; int c_lflag; int c_iflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_Show () ; 
 int /*<<< orphan*/  CON_SigCont ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int ECHO ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  Field_Clear (int /*<<< orphan*/ *) ; 
 int ICANON ; 
 int INPCK ; 
 int ISTRIP ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGTTIN ; 
 int /*<<< orphan*/  SIGTTOU ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 int /*<<< orphan*/  TTY_con ; 
 int TTY_eof ; 
 int TTY_erase ; 
 struct termios TTY_tc ; 
 size_t VEOF ; 
 size_t VERASE ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* qfalse ; 
 void* qtrue ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdinIsATTY ; 
 void* stdin_active ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 int ttycon_hide ; 
 void* ttycon_on ; 

void CON_Init( void )
{
	struct termios tc;

	// If the process is backgrounded (running non interactively)
	// then SIGTTIN or SIGTOU is emitted, if not caught, turns into a SIGSTP
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);

	// If SIGCONT is received, reinitialize console
	signal(SIGCONT, CON_SigCont);

	// Make stdin reads non-blocking
	fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) | O_NONBLOCK );

	if (!stdinIsATTY)
	{
		Com_Printf("tty console mode disabled\n");
		ttycon_on = qfalse;
		stdin_active = qtrue;
		return;
	}

	Field_Clear(&TTY_con);
	tcgetattr (STDIN_FILENO, &TTY_tc);
	TTY_erase = TTY_tc.c_cc[VERASE];
	TTY_eof = TTY_tc.c_cc[VEOF];
	tc = TTY_tc;

	/*
	ECHO: don't echo input characters
	ICANON: enable canonical mode.  This  enables  the  special
	characters  EOF,  EOL,  EOL2, ERASE, KILL, REPRINT,
	STATUS, and WERASE, and buffers by lines.
	ISIG: when any of the characters  INTR,  QUIT,  SUSP,  or
	DSUSP are received, generate the corresponding signal
	*/
	tc.c_lflag &= ~(ECHO | ICANON);

	/*
	ISTRIP strip off bit 8
	INPCK enable input parity checking
	*/
	tc.c_iflag &= ~(ISTRIP | INPCK);
	tc.c_cc[VMIN] = 1;
	tc.c_cc[VTIME] = 0;
	tcsetattr (STDIN_FILENO, TCSADRAIN, &tc);
	ttycon_on = qtrue;
	ttycon_hide = 1; // Mark as hidden, so prompt is shown in CON_Show
	CON_Show();
}