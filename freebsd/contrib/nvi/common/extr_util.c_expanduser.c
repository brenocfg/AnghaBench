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
struct passwd {char* pw_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 char* getlogin () ; 
 struct passwd* getpwnam (char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 scalar_t__ issetugid () ; 
 char* join (char*,char*) ; 
 char* strndup (char*,int) ; 

char *
expanduser(char *str)
{
	struct passwd *pwd;
	char *p, *t, *u, *h;

	/*
	 * This function always expands the content between the
	 * leading '~' and the first '/' or '\0' from the input.
	 * Return NULL whenever we fail to do so.
	 */
	if (*str != '~')
		return (NULL);
	p = str + 1;
	for (t = p; *t != '/' && *t != '\0'; ++t)
		continue;
	if (t == p) {
		/* ~ */
		if (issetugid() != 0 ||
		    (h = getenv("HOME")) == NULL) {
			if (((h = getlogin()) != NULL &&
			     (pwd = getpwnam(h)) != NULL) ||
			    (pwd = getpwuid(getuid())) != NULL)
				h = pwd->pw_dir;
			else
				return (NULL);
		}
	} else {
		/* ~user */
		if ((u = strndup(p, t - p)) == NULL)
			return (NULL);
		if ((pwd = getpwnam(u)) == NULL) {
			free(u);
			return (NULL);
		} else
			h = pwd->pw_dir;
		free(u);
	}

	for (; *t == '/' && *t != '\0'; ++t)
		continue;
	return (join(h, t));
}