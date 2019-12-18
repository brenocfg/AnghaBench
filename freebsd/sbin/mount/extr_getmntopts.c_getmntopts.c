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
struct mntopt {int m_inverse; int m_flag; scalar_t__ m_altloc; int /*<<< orphan*/ * m_option; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getmnt_silent ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ strncasecmp (char*,int /*<<< orphan*/ *,int) ; 
 char* strtok (char*,char*) ; 

void
getmntopts(const char *options, const struct mntopt *m0, int *flagp,
	int *altflagp)
{
	const struct mntopt *m;
	int negative, len;
	char *opt, *optbuf, *p;
	int *thisflagp;

	/* Copy option string, since it is about to be torn asunder... */
	if ((optbuf = strdup(options)) == NULL)
		err(1, NULL);

	for (opt = optbuf; (opt = strtok(opt, ",")) != NULL; opt = NULL) {
		/* Check for "no" prefix. */
		if (opt[0] == 'n' && opt[1] == 'o') {
			negative = 1;
			opt += 2;
		} else
			negative = 0;

		/*
		 * for options with assignments in them (ie. quotas)
		 * ignore the assignment as it's handled elsewhere
		 */
		p = strchr(opt, '=');
		if (p != NULL)
			 *++p = '\0';

		/* Scan option table. */
		for (m = m0; m->m_option != NULL; ++m) {
			len = strlen(m->m_option);
			if (strncasecmp(opt, m->m_option, len) == 0)
				if (opt[len] == '\0' || opt[len] == '=')
					break;
		}

		/* Save flag, or fail if option is not recognized. */
		if (m->m_option) {
			thisflagp = m->m_altloc ? altflagp : flagp;
			if (negative == m->m_inverse)
				*thisflagp |= m->m_flag;
			else
				*thisflagp &= ~m->m_flag;
		} else if (!getmnt_silent) {
			errx(1, "-o %s: option not supported", opt);
		}
	}

	free(optbuf);
}