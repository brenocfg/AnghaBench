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
typedef  int /*<<< orphan*/  user ;
typedef  scalar_t__ uid_t ;
typedef  int u_int ;
struct passwd {char* pw_dir; } ;

/* Variables and functions */
 scalar_t__ PATH_MAX ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 struct passwd* getpwnam (char*) ; 
 struct passwd* getpwuid (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* strchr (char const*,char) ; 
 int strlen (char*) ; 
 scalar_t__ xasprintf (char**,char*,char*,char const*,char const*) ; 
 char* xstrdup (char const*) ; 

char *
tilde_expand_filename(const char *filename, uid_t uid)
{
	const char *path, *sep;
	char user[128], *ret;
	struct passwd *pw;
	u_int len, slash;

	if (*filename != '~')
		return (xstrdup(filename));
	filename++;

	path = strchr(filename, '/');
	if (path != NULL && path > filename) {		/* ~user/path */
		slash = path - filename;
		if (slash > sizeof(user) - 1)
			fatal("tilde_expand_filename: ~username too long");
		memcpy(user, filename, slash);
		user[slash] = '\0';
		if ((pw = getpwnam(user)) == NULL)
			fatal("tilde_expand_filename: No such user %s", user);
	} else if ((pw = getpwuid(uid)) == NULL)	/* ~/path */
		fatal("tilde_expand_filename: No such uid %ld", (long)uid);

	/* Make sure directory has a trailing '/' */
	len = strlen(pw->pw_dir);
	if (len == 0 || pw->pw_dir[len - 1] != '/')
		sep = "/";
	else
		sep = "";

	/* Skip leading '/' from specified path */
	if (path != NULL)
		filename = path + 1;

	if (xasprintf(&ret, "%s%s%s", pw->pw_dir, sep, filename) >= PATH_MAX)
		fatal("tilde_expand_filename: Path too long");

	return (ret);
}