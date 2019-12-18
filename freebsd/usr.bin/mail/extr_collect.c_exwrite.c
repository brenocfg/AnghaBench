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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  Fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Fopen (char*,char*) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
exwrite(char name[], FILE *fp, int f)
{
	FILE *of;
	int c, lc;
	long cc;
	struct stat junk;

	if (f) {
		printf("\"%s\" ", name);
		(void)fflush(stdout);
	}
	if (stat(name, &junk) >= 0 && S_ISREG(junk.st_mode)) {
		if (!f)
			fprintf(stderr, "%s: ", name);
		fprintf(stderr, "File exists\n");
		return (-1);
	}
	if ((of = Fopen(name, "w")) == NULL) {
		warn((char *)NULL);
		return (-1);
	}
	lc = 0;
	cc = 0;
	while ((c = getc(fp)) != EOF) {
		cc++;
		if (c == '\n')
			lc++;
		(void)putc(c, of);
		if (ferror(of)) {
			warnx("%s", name);
			(void)Fclose(of);
			return (-1);
		}
	}
	(void)Fclose(of);
	printf("%d/%ld\n", lc, cc);
	(void)fflush(stdout);
	return (0);
}