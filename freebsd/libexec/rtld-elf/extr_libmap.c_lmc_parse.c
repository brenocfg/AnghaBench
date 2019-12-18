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
typedef  int /*<<< orphan*/  line ;

/* Variables and functions */
 int MAXPATHLEN ; 
 scalar_t__ iseol (char) ; 
 int /*<<< orphan*/  lm_add (char*,char*,char*) ; 
 int /*<<< orphan*/  lmc_parse_dir (char*) ; 
 int /*<<< orphan*/  lmc_parse_file (char*) ; 
 scalar_t__ rtld_isspace (char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlcpy (char*,char*,int) ; 

__attribute__((used)) static void
lmc_parse(char *lm_p, size_t lm_len)
{
	char *cp, *f, *t, *c, *p;
	char prog[MAXPATHLEN];
	/* allow includedir + full length path */
	char line[MAXPATHLEN + 13];
	size_t cnt, i;

	cnt = 0;
	p = NULL;
	while (cnt < lm_len) {
		i = 0;
		while (cnt < lm_len && lm_p[cnt] != '\n' &&
		    i < sizeof(line) - 1) {
			line[i] = lm_p[cnt];
			cnt++;
			i++;
		}
		line[i] = '\0';
		while (cnt < lm_len && lm_p[cnt] != '\n')
			cnt++;
		/* skip over nl */
		cnt++;

		cp = &line[0];
		t = f = c = NULL;

		/* Skip over leading space */
		while (rtld_isspace(*cp))
			cp++;

		/* Found a comment or EOL */
		if (iseol(*cp))
			continue;

		/* Found a constraint selector */
		if (*cp == '[') {
			cp++;

			/* Skip leading space */
			while (rtld_isspace(*cp))
				cp++;

			/* Found comment, EOL or end of selector */
			if  (iseol(*cp) || *cp == ']')
				continue;

			c = cp++;
			/* Skip to end of word */
			while (!rtld_isspace(*cp) && !iseol(*cp) && *cp != ']')
				cp++;

			/* Skip and zero out trailing space */
			while (rtld_isspace(*cp))
				*cp++ = '\0';

			/* Check if there is a closing brace */
			if (*cp != ']')
				continue;

			/* Terminate string if there was no trailing space */
			*cp++ = '\0';

			/*
			 * There should be nothing except whitespace or comment
			  from this point to the end of the line.
			 */
			while (rtld_isspace(*cp))
				cp++;
			if (!iseol(*cp))
				continue;

			if (strlcpy(prog, c, sizeof prog) >= sizeof prog)
				continue;
			p = prog;
			continue;
		}

		/* Parse the 'from' candidate. */
		f = cp++;
		while (!rtld_isspace(*cp) && !iseol(*cp))
			cp++;

		/* Skip and zero out the trailing whitespace */
		while (rtld_isspace(*cp))
			*cp++ = '\0';

		/* Found a comment or EOL */
		if (iseol(*cp))
			continue;

		/* Parse 'to' mapping */
		t = cp++;
		while (!rtld_isspace(*cp) && !iseol(*cp))
			cp++;

		/* Skip and zero out the trailing whitespace */
		while (rtld_isspace(*cp))
			*cp++ = '\0';

		/* Should be no extra tokens at this point */
		if (!iseol(*cp))
			continue;

		*cp = '\0';
		if (strcmp(f, "includedir") == 0)
			lmc_parse_dir(t);
		else if (strcmp(f, "include") == 0)
			lmc_parse_file(t);
		else
			lm_add(p, f, t);
	}
}