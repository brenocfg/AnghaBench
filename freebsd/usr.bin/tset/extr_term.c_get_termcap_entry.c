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
struct ttyent {char* ty_type; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 char* askuser (char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 void* getenv (char*) ; 
 struct ttyent* getttynam (char*) ; 
 char* mapped (char const*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 char* strrchr (char*,char) ; 
 char* tbuf ; 
 int tgetent (char*,char const*) ; 
 char* ttyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

const char *
get_termcap_entry(char *userarg, char **tcapbufp)
{
	struct ttyent *t;
	int rval;
	char *p, *ttypath;
	const char *ttype;

	if (userarg) {
		ttype = userarg;
		goto found;
	}

	/* Try the environment. */
	if ((ttype = getenv("TERM")))
		goto map;

	/* Try ttyname(3); check for dialup or other mapping. */
	if ((ttypath = ttyname(STDERR_FILENO))) {
		if ((p = strrchr(ttypath, '/')))
			++p;
		else
			p = ttypath;
		if ((t = getttynam(p))) {
			ttype = t->ty_type;
			goto map;
		}
	}

	/* If still undefined, use "unknown". */
	ttype = "unknown";

map:	ttype = mapped(ttype);

	/*
	 * If not a path, remove TERMCAP from the environment so we get a
	 * real entry from /etc/termcap.  This prevents us from being fooled
	 * by out of date stuff in the environment.
	 */
found:	if ((p = getenv("TERMCAP")) != NULL && *p != '/')
		unsetenv("TERMCAP");

	/*
	 * ttype now contains a pointer to the type of the terminal.
	 * If the first character is '?', ask the user.
	 */
	if (ttype[0] == '?') {
		if (ttype[1] != '\0')
			ttype = askuser(ttype + 1);
		else
			ttype = askuser(NULL);
	}

	/* Find the termcap entry.  If it doesn't exist, ask the user. */
	while ((rval = tgetent(tbuf, ttype)) == 0) {
		warnx("terminal type %s is unknown", ttype);
		ttype = askuser(NULL);
	}
	if (rval == -1)
		errx(1, "termcap: %s", strerror(errno ? errno : ENOENT));
	*tcapbufp = tbuf;
	return (ttype);
}