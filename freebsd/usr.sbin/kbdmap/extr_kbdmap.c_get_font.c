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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int sscanf (char*,char*,int*,int*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 char* sysconfig ; 

__attribute__((used)) static char *
get_font(void)
{
	char line[256], buf[20];
	char *fnt = NULL;

	FILE *fp = fopen(sysconfig, "r");
	if (fp) {
		while (fgets(line, sizeof(line), fp)) {
			int a, b, matches;

			if (line[0] == '#')
				continue;

			matches = sscanf(line,
			    " font%dx%d = \"%20[-.0-9a-zA-Z_]",
			    &a, &b, buf);
			if (matches==3) {
				if (strcmp(buf, "NO")) {
					if (fnt)
						free(fnt);
					fnt = strdup(buf);
				}
			}
		}
		fclose(fp);
	} else
		fprintf(stderr, "Could not open %s for reading\n", sysconfig);

	return fnt;
}