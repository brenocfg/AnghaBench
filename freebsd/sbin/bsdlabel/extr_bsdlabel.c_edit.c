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
struct disklabel {int dummy; } ;
typedef  int /*<<< orphan*/  label ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  display (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  editit () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int getasciilabel (int /*<<< orphan*/ *,struct disklabel*) ; 
 int getchar () ; 
 struct disklabel lab ; 
 int mkstemp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  tmpfil ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ writelabel () ; 

__attribute__((used)) static int
edit(void)
{
	int c, fd;
	struct disklabel label;
	FILE *fp;

	if ((fd = mkstemp(tmpfil)) == -1 ||
	    (fp = fdopen(fd, "w")) == NULL) {
		warnx("can't create %s", tmpfil);
		return (1);
	}
	display(fp, NULL);
	fclose(fp);
	for (;;) {
		if (!editit())
			break;
		fp = fopen(tmpfil, "r");
		if (fp == NULL) {
			warnx("can't reopen %s for reading", tmpfil);
			break;
		}
		bzero((char *)&label, sizeof(label));
		c = getasciilabel(fp, &label);
		fclose(fp);
		if (c) {
			lab = label;
			if (writelabel() == 0) {
				(void) unlink(tmpfil);
				return (0);
			}
		}
		printf("re-edit the label? [y]: ");
		fflush(stdout);
		c = getchar();
		if (c != EOF && c != (int)'\n')
			while (getchar() != (int)'\n')
				;
		if  (c == (int)'n')
			break;
	}
	(void) unlink(tmpfil);
	return (1);
}