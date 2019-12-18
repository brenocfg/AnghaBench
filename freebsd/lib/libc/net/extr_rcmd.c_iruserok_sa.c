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
struct stat {int st_mode; scalar_t__ st_uid; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct passwd {scalar_t__ pw_uid; int /*<<< orphan*/  pw_dir; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int /*<<< orphan*/  pbuf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  S_ISREG (int) ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 char* _PATH_HEQUIV ; 
 scalar_t__ __check_rhosts_file ; 
 scalar_t__ __ivaliduser_sa (int /*<<< orphan*/ *,struct sockaddr const*,int,char const*,char const*) ; 
 char* __rcmd_errstr ; 
 scalar_t__ _fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ geteuid () ; 
 struct passwd* getpwnam (char const*) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_storage*,void const*,int) ; 
 int /*<<< orphan*/  seteuid (scalar_t__) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

int
iruserok_sa(const void *ra, int rlen, int superuser, const char *ruser,
    const char *luser)
{
	char *cp;
	struct stat sbuf;
	struct passwd *pwd;
	FILE *hostf;
	uid_t uid;
	int first;
	char pbuf[MAXPATHLEN];
	const struct sockaddr *raddr;
	struct sockaddr_storage ss;

	/* avoid alignment issue */
	if (rlen > sizeof(ss)) 
		return(-1);
	memcpy(&ss, ra, rlen);
	raddr = (struct sockaddr *)&ss;

	first = 1;
	hostf = superuser ? NULL : fopen(_PATH_HEQUIV, "re");
again:
	if (hostf) {
		if (__ivaliduser_sa(hostf, raddr, rlen, luser, ruser) == 0) {
			(void)fclose(hostf);
			return (0);
		}
		(void)fclose(hostf);
	}
	if (first == 1 && (__check_rhosts_file || superuser)) {
		first = 0;
		if ((pwd = getpwnam(luser)) == NULL)
			return (-1);
		(void)strlcpy(pbuf, pwd->pw_dir, sizeof(pbuf));
		(void)strlcat(pbuf, "/.rhosts", sizeof(pbuf));

		/*
		 * Change effective uid while opening .rhosts.  If root and
		 * reading an NFS mounted file system, can't read files that
		 * are protected read/write owner only.
		 */
		uid = geteuid();
		(void)seteuid(pwd->pw_uid);
		hostf = fopen(pbuf, "re");
		(void)seteuid(uid);

		if (hostf == NULL)
			return (-1);
		/*
		 * If not a regular file, or is owned by someone other than
		 * user or root or if writeable by anyone but the owner, quit.
		 */
		cp = NULL;
		if (lstat(pbuf, &sbuf) < 0)
			cp = ".rhosts lstat failed";
		else if (!S_ISREG(sbuf.st_mode))
			cp = ".rhosts not regular file";
		else if (_fstat(fileno(hostf), &sbuf) < 0)
			cp = ".rhosts fstat failed";
		else if (sbuf.st_uid && sbuf.st_uid != pwd->pw_uid)
			cp = "bad .rhosts owner";
		else if (sbuf.st_mode & (S_IWGRP|S_IWOTH))
			cp = ".rhosts writeable by other than owner";
		/* If there were any problems, quit. */
		if (cp) {
			__rcmd_errstr = cp;
			(void)fclose(hostf);
			return (-1);
		}
		goto again;
	}
	return (-1);
}