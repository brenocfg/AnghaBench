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
struct passwd {char const* pw_dir; } ;
typedef  int /*<<< orphan*/  pwbuf ;

/* Variables and functions */
 char* el_calloc (size_t,int) ; 
 int /*<<< orphan*/  el_free (char*) ; 
 struct passwd* getpwnam (char*) ; 
 struct passwd* getpwnam_r (char*,struct passwd*,char*,int,...) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 struct passwd* getpwuid_r (int /*<<< orphan*/ ,struct passwd*,char*,int,...) ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,char const*) ; 
 char* strchr (char const*,char) ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

char *
fn_tilde_expand(const char *txt)
{
#if defined(HAVE_GETPW_R_POSIX) || defined(HAVE_GETPW_R_DRAFT)
	struct passwd pwres;
	char pwbuf[1024];
#endif
	struct passwd *pass;
	char *temp;
	size_t len = 0;

	if (txt[0] != '~')
		return strdup(txt);

	temp = strchr(txt + 1, '/');
	if (temp == NULL) {
		temp = strdup(txt + 1);
		if (temp == NULL)
			return NULL;
	} else {
		/* text until string after slash */
		len = (size_t)(temp - txt + 1);
		temp = el_calloc(len, sizeof(*temp));
		if (temp == NULL)
			return NULL;
		(void)strncpy(temp, txt + 1, len - 2);
		temp[len - 2] = '\0';
	}
	if (temp[0] == 0) {
#ifdef HAVE_GETPW_R_POSIX
		if (getpwuid_r(getuid(), &pwres, pwbuf, sizeof(pwbuf),
		    &pass) != 0)
			pass = NULL;
#elif HAVE_GETPW_R_DRAFT
		pass = getpwuid_r(getuid(), &pwres, pwbuf, sizeof(pwbuf));
#else
		pass = getpwuid(getuid());
#endif
	} else {
#ifdef HAVE_GETPW_R_POSIX
		if (getpwnam_r(temp, &pwres, pwbuf, sizeof(pwbuf), &pass) != 0)
			pass = NULL;
#elif HAVE_GETPW_R_DRAFT
		pass = getpwnam_r(temp, &pwres, pwbuf, sizeof(pwbuf));
#else
		pass = getpwnam(temp);
#endif
	}
	el_free(temp);		/* value no more needed */
	if (pass == NULL)
		return strdup(txt);

	/* update pointer txt to point at string immedially following */
	/* first slash */
	txt += len;

	len = strlen(pass->pw_dir) + 1 + strlen(txt) + 1;
	temp = el_calloc(len, sizeof(*temp));
	if (temp == NULL)
		return NULL;
	(void)snprintf(temp, len, "%s/%s", pass->pw_dir, txt);

	return temp;
}