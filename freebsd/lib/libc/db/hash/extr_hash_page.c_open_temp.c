#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  path ;
struct TYPE_3__ {int fp; } ;
typedef  TYPE_1__ HTAB ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  __libc_sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 char* getenv (char*) ; 
 scalar_t__ issetugid () ; 
 int mkostemp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int
open_temp(HTAB *hashp)
{
	sigset_t set, oset;
	int len;
	char *envtmp = NULL;
	char path[MAXPATHLEN];

	if (issetugid() == 0)
		envtmp = getenv("TMPDIR");
	len = snprintf(path,
	    sizeof(path), "%s/_hash.XXXXXX", envtmp ? envtmp : "/tmp");
	if (len < 0 || len >= (int)sizeof(path)) {
		errno = ENAMETOOLONG;
		return (-1);
	}

	/* Block signals; make sure file goes away at process exit. */
	(void)sigfillset(&set);
	(void)__libc_sigprocmask(SIG_BLOCK, &set, &oset);
	if ((hashp->fp = mkostemp(path, O_CLOEXEC)) != -1)
		(void)unlink(path);
	(void)__libc_sigprocmask(SIG_SETMASK, &oset, (sigset_t *)NULL);
	return (hashp->fp != -1 ? 0 : -1);
}