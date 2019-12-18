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
typedef  int /*<<< orphan*/  time_t ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  Fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Fopen (char*,char*) ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 char* myname ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int umask (int) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
savemail(char name[], FILE *fi)
{
	FILE *fo;
	char buf[BUFSIZ];
	int i;
	time_t now;
	mode_t saved_umask;

	saved_umask = umask(077);
	fo = Fopen(name, "a");
	umask(saved_umask);

	if (fo == NULL) {
		warn("%s", name);
		return (-1);
	}
	(void)time(&now);
	fprintf(fo, "From %s %s", myname, ctime(&now));
	while ((i = fread(buf, 1, sizeof(buf), fi)) > 0)
		(void)fwrite(buf, 1, i, fo);
	fprintf(fo, "\n");
	(void)fflush(fo);
	if (ferror(fo))
		warn("%s", name);
	(void)Fclose(fo);
	rewind(fi);
	return (0);
}