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
 int /*<<< orphan*/  asprintf (char**,char*,char const*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int sscanf (char*,char*,int*,int*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char const*) ; 
 char* strrchr (char*,char) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  system (char*) ; 
 scalar_t__ using_vt ; 
 scalar_t__ verbose ; 
 scalar_t__ x11 ; 

__attribute__((used)) static void
vidcontrol(const char *fnt)
{
	char *tmp, *p, *q, *cmd;
	char ch;
	int i;

	/* syscons test failed */
	if (x11)
		return;

	if (using_vt) {
		asprintf(&cmd, "vidcontrol -f %s", fnt);
		system(cmd);
		free(cmd);
		return;
	}

	tmp = strdup(fnt);

	/* Extract font size */
	p = strrchr(tmp, '-');
	if (p && p[1] != '\0') {
		p++;
		/* Remove any '.fnt' extension */
		if ((q = strstr(p, ".fnt")))
			*q = '\0';

		/*
		 * Check font size is valid, with no trailing characters
		 *  ('&ch' should not be matched)
		 */
		if (sscanf(p, "%dx%d%c", &i, &i, &ch) != 2)
			fprintf(stderr, "Which font size? %s\n", fnt);
		else {
			asprintf(&cmd, "vidcontrol -f %s %s", p, fnt);
			if (verbose)
				fprintf(stderr, "%s\n", cmd);
			system(cmd);
			free(cmd);
		}
	} else
		fprintf(stderr, "Which font size? %s\n", fnt);

	free(tmp);
}