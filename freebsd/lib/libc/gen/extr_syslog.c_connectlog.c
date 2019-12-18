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
struct sockaddr_un {int sun_len; int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  SyslogAddr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 scalar_t__ CONNDEF ; 
 scalar_t__ CONNPRIV ; 
 int LogFile ; 
 scalar_t__ NOCONN ; 
 int SOCK_CLOEXEC ; 
 int SOCK_DGRAM ; 
 int /*<<< orphan*/  _PATH_LOG ; 
 int /*<<< orphan*/  _PATH_LOG_PRIV ; 
 int /*<<< orphan*/  _PATH_OLDLOG ; 
 int /*<<< orphan*/  _close (int) ; 
 int _connect (int,struct sockaddr*,int) ; 
 int _socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ status ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
connectlog(void)
{
	struct sockaddr_un SyslogAddr;	/* AF_UNIX address of local logger */

	if (LogFile == -1) {
		if ((LogFile = _socket(AF_UNIX, SOCK_DGRAM | SOCK_CLOEXEC,
		    0)) == -1)
			return;
	}
	if (LogFile != -1 && status == NOCONN) {
		SyslogAddr.sun_len = sizeof(SyslogAddr);
		SyslogAddr.sun_family = AF_UNIX;

		/*
		 * First try privileged socket. If no success,
		 * then try default socket.
		 */
		(void)strncpy(SyslogAddr.sun_path, _PATH_LOG_PRIV,
		    sizeof SyslogAddr.sun_path);
		if (_connect(LogFile, (struct sockaddr *)&SyslogAddr,
		    sizeof(SyslogAddr)) != -1)
			status = CONNPRIV;

		if (status == NOCONN) {
			(void)strncpy(SyslogAddr.sun_path, _PATH_LOG,
			    sizeof SyslogAddr.sun_path);
			if (_connect(LogFile, (struct sockaddr *)&SyslogAddr,
			    sizeof(SyslogAddr)) != -1)
				status = CONNDEF;
		}

		if (status == NOCONN) {
			/*
			 * Try the old "/dev/log" path, for backward
			 * compatibility.
			 */
			(void)strncpy(SyslogAddr.sun_path, _PATH_OLDLOG,
			    sizeof SyslogAddr.sun_path);
			if (_connect(LogFile, (struct sockaddr *)&SyslogAddr,
			    sizeof(SyslogAddr)) != -1)
				status = CONNDEF;
		}

		if (status == NOCONN) {
			(void)_close(LogFile);
			LogFile = -1;
		}
	}
}