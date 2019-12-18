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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int C_OPTION ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/ * soelim_fopen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
soelim_file(FILE *f, int flag)
{
	char *line = NULL;
	char *walk, *cp;
	size_t linecap = 0;
	ssize_t linelen;

	if (f == NULL)
		return (1);

	while ((linelen = getline(&line, &linecap, f)) > 0) {
		if (strncmp(line, ".so", 3) != 0) {
			printf("%s", line);
			continue;
		}

		walk = line + 3;
		if (!isspace(*walk) && ((flag & C_OPTION) == 0)) {
			printf("%s", line);
			continue;
		}

		while (isspace(*walk))
			walk++;

		cp = walk;
		while (*cp != '\0' && !isspace(*cp))
			cp++;
		*cp = 0;
		if (cp < line + linelen)
			cp++;

		if (*walk == '\0') {
			printf("%s", line);
			continue;
		}
		if (soelim_file(soelim_fopen(walk), flag) == 1) {
			free(line);
			return (1);
		}
		if (*cp != '\0')
			printf("%s", cp);
	}

	free(line);
	fclose(f);

	return (0);
}