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

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  maybe_err (char*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static void
prepend_gzip(char *gzip, int *argc, char ***argv)
{
	char *s, **nargv, **ac;
	int nenvarg = 0, i;

	/* scan how many arguments there are */
	for (s = gzip;;) {
		while (*s == ' ' || *s == '\t')
			s++;
		if (*s == 0)
			goto count_done;
		nenvarg++;
		while (*s != ' ' && *s != '\t')
			if (*s++ == 0)
				goto count_done;
	}
count_done:
	/* punt early */
	if (nenvarg == 0)
		return;

	*argc += nenvarg;
	ac = *argv;

	nargv = (char **)malloc((*argc + 1) * sizeof(char *));
	if (nargv == NULL)
		maybe_err("malloc");

	/* stash this away */
	*argv = nargv;

	/* copy the program name first */
	i = 0;
	nargv[i++] = *(ac++);

	/* take a copy of $GZIP and add it to the array */
	s = strdup(gzip);
	if (s == NULL)
		maybe_err("strdup");
	for (;;) {
		/* Skip whitespaces. */
		while (*s == ' ' || *s == '\t')
			s++;
		if (*s == 0)
			goto copy_done;
		nargv[i++] = s;
		/* Find the end of this argument. */
		while (*s != ' ' && *s != '\t')
			if (*s++ == 0)
				/* Argument followed by NUL. */
				goto copy_done;
		/* Terminate by overwriting ' ' or '\t' with NUL. */
		*s++ = 0;
	}
copy_done:

	/* copy the original arguments and a NULL */
	while (*ac)
		nargv[i++] = *(ac++);
	nargv[i] = NULL;
}