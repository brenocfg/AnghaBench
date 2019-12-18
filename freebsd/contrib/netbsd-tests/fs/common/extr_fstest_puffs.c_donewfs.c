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
typedef  int /*<<< orphan*/  sv ;
struct puffstestargs {int pta_pflags; int* pta_dir; int* pta_dev; int pta_pargslen; int* pta_pargs; int pta_servfd; int /*<<< orphan*/  pta_childpid; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  mntflags ;
typedef  int /*<<< orphan*/  len ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 size_t MAXPATHLEN ; 
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  childfail ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int errno ; 
 int execvp (char*,char**) ; 
 int /*<<< orphan*/  fork () ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (struct puffstestargs*,int /*<<< orphan*/ ,int) ; 
 int setenv (char*,char*,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  strlcpy (int*,char const*,int) ; 
 struct puffstestargs* theargs ; 
 int xread (int,...) ; 

__attribute__((used)) static int
donewfs(const atf_tc_t *tc, void **argp,
	const char *image, off_t size, void *fspriv, char **theargv)
{
	struct puffstestargs *args;
	pid_t childpid;
	int *pflags;
	char comfd[16];
	int sv[2];
	int mntflags;
	size_t len;
	ssize_t n;

	*argp = NULL;

	args = malloc(sizeof(*args));
	if (args == NULL)
		return errno;
	memset(args, 0, sizeof(*args));

	pflags = &args->pta_pflags;

	/* Create sucketpair for communication with the real file server */
	if (socketpair(PF_LOCAL, SOCK_STREAM, 0, sv) == -1)
		return errno;

	signal(SIGCHLD, childfail);

	switch ((childpid = fork())) {
	case 0:
		close(sv[1]);
		snprintf(comfd, sizeof(sv[0]), "%d", sv[0]);
		if (setenv("PUFFS_COMFD", comfd, 1) == -1)
			return errno;

		if (execvp(theargv[0], theargv) == -1)
			return errno;
	case -1:
		return errno;
	default:
		close(sv[0]);
		break;
	}

	/* read args */
	if ((n = xread(sv[1], &len, sizeof(len))) != sizeof(len))
		err(1, "mp 1 %zd", n);
	if (len > MAXPATHLEN)
		err(1, "mntpath > MAXPATHLEN");
	if ((size_t)xread(sv[1], args->pta_dir, len) != len)
		err(1, "mp 2");
	if (xread(sv[1], &len, sizeof(len)) != sizeof(len))
		err(1, "fn 1");
	if (len > MAXPATHLEN)
		err(1, "devpath > MAXPATHLEN");
	if ((size_t)xread(sv[1], args->pta_dev, len) != len)
		err(1, "fn 2");
	if (xread(sv[1], &mntflags, sizeof(mntflags)) != sizeof(mntflags))
		err(1, "mntflags");
	if (xread(sv[1], &args->pta_pargslen, sizeof(args->pta_pargslen))
	    != sizeof(args->pta_pargslen))
		err(1, "puffstest_args len");
	args->pta_pargs = malloc(args->pta_pargslen);
	if (args->pta_pargs == NULL)
		err(1, "malloc");
	if (xread(sv[1], args->pta_pargs, args->pta_pargslen)
	    != (ssize_t)args->pta_pargslen)
		err(1, "puffstest_args");
	if (xread(sv[1], pflags, sizeof(*pflags)) != sizeof(*pflags))
		err(1, "pflags");

	args->pta_childpid = childpid;
	args->pta_servfd = sv[1];
	strlcpy(args->pta_dev, image, sizeof(args->pta_dev));

	*argp = theargs = args;

	return 0;
}