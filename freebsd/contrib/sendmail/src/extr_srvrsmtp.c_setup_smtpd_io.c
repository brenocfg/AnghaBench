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
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  InChannel ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int LogLevel ; 
 int /*<<< orphan*/  NOQID ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  OutChannel ; 
 int /*<<< orphan*/  SM_IO_WHAT_FD ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 scalar_t__ bitset (int,int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ isatty (int) ; 
 int /*<<< orphan*/  sm_errstring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm_io_automode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sm_io_getinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sm_syslog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  smioout ; 
 scalar_t__ tTd (int,int) ; 

__attribute__((used)) static void
setup_smtpd_io()
{
	int inchfd, outchfd, outfd;

	inchfd = sm_io_getinfo(InChannel, SM_IO_WHAT_FD, NULL);
	outchfd  = sm_io_getinfo(OutChannel, SM_IO_WHAT_FD, NULL);
	outfd = sm_io_getinfo(smioout, SM_IO_WHAT_FD, NULL);
	if (outchfd != outfd)
	{
		/* arrange for debugging output to go to remote host */
		(void) dup2(outchfd, outfd);
	}

	/*
	**  if InChannel and OutChannel are stdin/stdout
	**  and connected to ttys
	**  and fcntl(STDIN, F_SETFL, O_NONBLOCKING) also changes STDOUT,
	**  then "chain" them together.
	*/

	if (inchfd == STDIN_FILENO && outchfd == STDOUT_FILENO &&
	    isatty(inchfd) && isatty(outchfd))
	{
		int inmode, outmode;

		inmode = fcntl(inchfd, F_GETFL, 0);
		if (inmode == -1)
		{
			if (LogLevel > 11)
				sm_syslog(LOG_INFO, NOQID,
					"fcntl(inchfd, F_GETFL) failed: %s",
					sm_errstring(errno));
			return;
		}
		outmode = fcntl(outchfd, F_GETFL, 0);
		if (outmode == -1)
		{
			if (LogLevel > 11)
				sm_syslog(LOG_INFO, NOQID,
					"fcntl(outchfd, F_GETFL) failed: %s",
					sm_errstring(errno));
			return;
		}
		if (bitset(O_NONBLOCK, inmode) ||
		    bitset(O_NONBLOCK, outmode) ||
		    fcntl(inchfd, F_SETFL, inmode | O_NONBLOCK) == -1)
			return;
		outmode = fcntl(outchfd, F_GETFL, 0);
		if (outmode != -1 && bitset(O_NONBLOCK, outmode))
		{
			/* changing InChannel also changes OutChannel */
			sm_io_automode(OutChannel, InChannel);
			if (tTd(97, 4) && LogLevel > 9)
				sm_syslog(LOG_INFO, NOQID,
					  "set automode for I (%d)/O (%d) in SMTP server",
					  inchfd, outchfd);
		}

		/* undo change of inchfd */
		(void) fcntl(inchfd, F_SETFL, inmode);
	}
}