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
typedef  scalar_t__ uid_t ;
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  controladdr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 scalar_t__ ControlSocket ; 
 char* ControlSocketName ; 
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  LOG_ALERT ; 
 int /*<<< orphan*/  NOQID ; 
 int /*<<< orphan*/  RunAsGid ; 
 scalar_t__ RunAsUid ; 
 int /*<<< orphan*/  RunAsUserName ; 
 long SFF_CREAT ; 
 long SFF_MUSTOWN ; 
 long SFF_NOLINK ; 
 long SFF_OPENASROOT ; 
 long SFF_SAFEDIRPATH ; 
 scalar_t__ SM_FD_SETSIZE ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 scalar_t__ TrustedUid ; 
 scalar_t__ bind (scalar_t__,struct sockaddr*,int) ; 
 scalar_t__ chmod (char*,int) ; 
 scalar_t__ chown (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  closecontrolsocket (int) ; 
 int /*<<< orphan*/  clrcontrol () ; 
 int errno ; 
 scalar_t__ geteuid () ; 
 scalar_t__ listen (scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,char,int) ; 
 int /*<<< orphan*/  message (char*,char*,int,int /*<<< orphan*/ ) ; 
 int safefile (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sm_errstring (int) ; 
 int /*<<< orphan*/  sm_strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sm_syslog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

int
opencontrolsocket()
{
# if NETUNIX
	int save_errno;
	int rval;
	long sff = SFF_SAFEDIRPATH|SFF_OPENASROOT|SFF_NOLINK|SFF_CREAT|SFF_MUSTOWN;
	struct sockaddr_un controladdr;

	if (ControlSocketName == NULL || *ControlSocketName == '\0')
		return 0;

	if (strlen(ControlSocketName) >= sizeof(controladdr.sun_path))
	{
		errno = ENAMETOOLONG;
		return -1;
	}

	rval = safefile(ControlSocketName, RunAsUid, RunAsGid, RunAsUserName,
			sff, S_IRUSR|S_IWUSR, NULL);

	/* if not safe, don't create */
	if (rval != 0)
	{
		errno = rval;
		return -1;
	}

	ControlSocket = socket(AF_UNIX, SOCK_STREAM, 0);
	if (ControlSocket < 0)
		return -1;
	if (SM_FD_SETSIZE > 0 && ControlSocket >= SM_FD_SETSIZE)
	{
		clrcontrol();
		errno = EINVAL;
		return -1;
	}

	(void) unlink(ControlSocketName);
	memset(&controladdr, '\0', sizeof(controladdr));
	controladdr.sun_family = AF_UNIX;
	(void) sm_strlcpy(controladdr.sun_path, ControlSocketName,
			  sizeof(controladdr.sun_path));

	if (bind(ControlSocket, (struct sockaddr *) &controladdr,
		 sizeof(controladdr)) < 0)
	{
		save_errno = errno;
		clrcontrol();
		errno = save_errno;
		return -1;
	}

	if (geteuid() == 0)
	{
		uid_t u = 0;

		if (RunAsUid != 0)
			u = RunAsUid;
		else if (TrustedUid != 0)
			u = TrustedUid;

		if (u != 0 &&
		    chown(ControlSocketName, u, -1) < 0)
		{
			save_errno = errno;
			sm_syslog(LOG_ALERT, NOQID,
				  "ownership change on %s to uid %d failed: %s",
				  ControlSocketName, (int) u,
				  sm_errstring(save_errno));
			message("050 ownership change on %s to uid %d failed: %s",
				ControlSocketName, (int) u,
				sm_errstring(save_errno));
			closecontrolsocket(true);
			errno = save_errno;
			return -1;
		}
	}

	if (chmod(ControlSocketName, S_IRUSR|S_IWUSR) < 0)
	{
		save_errno = errno;
		closecontrolsocket(true);
		errno = save_errno;
		return -1;
	}

	if (listen(ControlSocket, 8) < 0)
	{
		save_errno = errno;
		closecontrolsocket(true);
		errno = save_errno;
		return -1;
	}
# endif /* NETUNIX */
	return 0;
}