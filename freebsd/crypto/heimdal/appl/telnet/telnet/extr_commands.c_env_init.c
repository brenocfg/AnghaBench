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
struct env_lst {char* value; scalar_t__ export; } ;
struct addrinfo {int /*<<< orphan*/ * ai_canonname; struct addrinfo* ai_next; int /*<<< orphan*/  ai_flags; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AI_CANONNAME ; 
 int asprintf (char**,char*,char*,char*) ; 
 struct env_lst* env_define (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  env_export (unsigned char*) ; 
 struct env_lst* env_find (unsigned char*) ; 
 int /*<<< orphan*/  env_unexport (unsigned char*) ; 
 char** environ ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

void
env_init(void)
{
	char **epp, *cp;
	struct env_lst *ep;

	for (epp = environ; *epp; epp++) {
		if ((cp = strchr(*epp, '='))) {
			*cp = '\0';
			ep = env_define((unsigned char *)*epp,
					(unsigned char *)cp+1);
			ep->export = 0;
			*cp = '=';
		}
	}
	/*
	 * Special case for DISPLAY variable.  If it is ":0.0" or
	 * "unix:0.0", we have to get rid of "unix" and insert our
	 * hostname.
	 */
	if ((ep = env_find((unsigned char*)"DISPLAY"))
	    && (*ep->value == ':'
	    || strncmp((char *)ep->value, "unix:", 5) == 0)) {
		char hbuf[256+1];
		char *cp2 = strchr((char *)ep->value, ':');
		int error;

		/* XXX - should be k_gethostname? */
		gethostname(hbuf, 256);
		hbuf[256] = '\0';

		/* If this is not the full name, try to get it via DNS */
		if (strchr(hbuf, '.') == 0) {
			struct addrinfo hints, *ai, *a;

			memset (&hints, 0, sizeof(hints));
			hints.ai_flags = AI_CANONNAME;

			error = getaddrinfo (hbuf, NULL, &hints, &ai);
			if (error == 0) {
				for (a = ai; a != NULL; a = a->ai_next)
					if (a->ai_canonname != NULL) {
						strlcpy (hbuf,
							 ai->ai_canonname,
							 256);
						break;
					}
				freeaddrinfo (ai);
			}
		}

		error = asprintf (&cp, "%s%s", hbuf, cp2);
		if (error != -1) {
		    free (ep->value);
		    ep->value = (unsigned char *)cp;
		}
	}
	/*
	 * If USER is not defined, but LOGNAME is, then add
	 * USER with the value from LOGNAME.  By default, we
	 * don't export the USER variable.
	 */
	if ((env_find((unsigned char*)"USER") == NULL) &&
	    (ep = env_find((unsigned char*)"LOGNAME"))) {
		env_define((unsigned char *)"USER", ep->value);
		env_unexport((unsigned char *)"USER");
	}
	env_export((unsigned char *)"DISPLAY");
	env_export((unsigned char *)"PRINTER");
	env_export((unsigned char *)"XAUTHORITY");
}