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
struct passwd {char* pw_dir; } ;
struct TYPE_3__ {int gl_flags; } ;
typedef  TYPE_1__ glob_t ;
typedef  scalar_t__ Char ;

/* Variables and functions */
 char CHAR_EOS ; 
 scalar_t__ const CHAR_SLASH ; 
 scalar_t__ const CHAR_TILDE ; 
 int GLOB_TILDE ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getuid () ; 
 struct passwd* k_getpwnam (char*) ; 
 struct passwd* k_getpwuid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const Char *
globtilde(const Char *pattern, Char *patbuf, glob_t *pglob)
{
	struct passwd *pwd;
	char *h;
	const Char *p;
	Char *b;

	if (*pattern != CHAR_TILDE || !(pglob->gl_flags & GLOB_TILDE))
		return pattern;

	/* Copy up to the end of the string or / */
	for (p = pattern + 1, h = (char *) patbuf; *p && *p != CHAR_SLASH;
	     *h++ = *p++)
		continue;

	*h = CHAR_EOS;

	if (((char *) patbuf)[0] == CHAR_EOS) {
		/*
		 * handle a plain ~ or ~/ by expanding $HOME
		 * first and then trying the password file
		 */
		if ((h = getenv("HOME")) == NULL) {
			if ((pwd = k_getpwuid(getuid())) == NULL)
				return pattern;
			else
				h = pwd->pw_dir;
		}
	}
	else {
		/*
		 * Expand a ~user
		 */
		if ((pwd = k_getpwnam((char*) patbuf)) == NULL)
			return pattern;
		else
			h = pwd->pw_dir;
	}

	/* Copy the home directory */
	for (b = patbuf; *h; *b++ = *h++)
		continue;

	/* Append the rest of the pattern */
	while ((*b++ = *p++) != CHAR_EOS)
		continue;

	return patbuf;
}