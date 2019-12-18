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
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  TRAILER ; 
 char* _PATH_TMP ; 
 int /*<<< orphan*/  __libc_sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _close (int) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char const*,char*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ issetugid () ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

FILE *
tmpfile(void)
{
	sigset_t set, oset;
	FILE *fp;
	int fd, sverrno;
#define	TRAILER	"tmp.XXXXXX"
	char *buf;
	const char *tmpdir;

	tmpdir = NULL;
	if (issetugid() == 0)
		tmpdir = getenv("TMPDIR");
	if (tmpdir == NULL)
		tmpdir = _PATH_TMP;

	(void)asprintf(&buf, "%s%s%s", tmpdir,
	    (tmpdir[strlen(tmpdir) - 1] == '/') ? "" : "/", TRAILER);
	if (buf == NULL)
		return (NULL);

	sigfillset(&set);
	(void)__libc_sigprocmask(SIG_BLOCK, &set, &oset);

	fd = mkstemp(buf);
	if (fd != -1)
		(void)unlink(buf);

	free(buf);

	(void)__libc_sigprocmask(SIG_SETMASK, &oset, NULL);

	if (fd == -1)
		return (NULL);

	if ((fp = fdopen(fd, "w+")) == NULL) {
		sverrno = errno;
		(void)_close(fd);
		errno = sverrno;
		return (NULL);
	}
	return (fp);
}