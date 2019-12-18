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
typedef  int /*<<< orphan*/  x ;
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  HOSTNAMEBASE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  __arraycount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc_uint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bindcalls ; 
 scalar_t__ doquit ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  hostnamebuf ; 
 int /*<<< orphan*/  hostnamemib ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  iskiller ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int mypid ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int rump_sys___sysctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rump_sys_bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  rump_sys_close (int) ; 
 int rump_sys_getpid () ; 
 int rump_sys_open (char*,int /*<<< orphan*/ ) ; 
 int rump_sys_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int rump_sys_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rump_sys_write (int,char*,int) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  syscalls ; 

__attribute__((used)) static void *
client(void *arg)
{
	char buf[256];
	struct sockaddr_in sin;
	size_t blen;
	int port = (int)(uintptr_t)arg;
	int s, fd, x;

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_len = sizeof(sin);
	sin.sin_port = htons(port);

	while (!doquit) {
		pid_t pidi;
		blen = sizeof(buf);
		s = rump_sys_socket(PF_INET, SOCK_STREAM, 0);
		if (s == -1)
			err(1, "socket");
		atomic_inc_uint(&syscalls);

		fd = rump_sys_open("/dev/null", O_RDWR);
		atomic_inc_uint(&syscalls);

		if (doquit)
			goto out;

		x = 1;
		if (rump_sys_setsockopt(s, SOL_SOCKET, SO_REUSEADDR,
		    &x, sizeof(x)) == -1)
			err(1, "reuseaddr");

		/*
		 * we don't really know when the kernel handles our disconnect,
		 * so be soft about about the failure in case of a killer client
		 */
		if (rump_sys_bind(s, (struct sockaddr*)&sin, sizeof(sin))==-1) {
			if (!iskiller)
				err(1, "bind to port %d failed",
				    ntohs(sin.sin_port));
		} else {
			atomic_inc_uint(&bindcalls);
		}
		atomic_inc_uint(&syscalls);

		if (doquit)
			goto out;

		if (rump_sys___sysctl(hostnamemib, __arraycount(hostnamemib),
		    buf, &blen, NULL, 0) == -1)
			err(1, "sysctl");
		if (strncmp(buf, hostnamebuf, sizeof(HOSTNAMEBASE)-1) != 0)
			errx(1, "hostname (%s/%s) mismatch", buf, hostnamebuf);
		atomic_inc_uint(&syscalls);

		if (doquit)
			goto out;

		pidi = rump_sys_getpid();
		if (pidi == -1)
			err(1, "getpid");
		if (pidi != mypid)
			errx(1, "mypid mismatch");
		atomic_inc_uint(&syscalls);

		if (doquit)
			goto out;

		if (rump_sys_write(fd, buf, 16) != 16)
			err(1, "write /dev/null");
		atomic_inc_uint(&syscalls);

 out:
		rump_sys_close(fd);
		atomic_inc_uint(&syscalls);
		rump_sys_close(s);
		atomic_inc_uint(&syscalls);
	}

	return NULL;
}