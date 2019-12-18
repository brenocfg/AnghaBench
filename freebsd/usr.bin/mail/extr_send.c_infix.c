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
typedef  int /*<<< orphan*/  tempname ;
struct header {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  Fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Fdopen (int,char*) ; 
 int /*<<< orphan*/ * Fopen (char*,char*) ; 
 int GBCC ; 
 int GCC ; 
 int GCOMMA ; 
 int GINREPLYTO ; 
 int GNL ; 
 int GREPLYTO ; 
 int GSUBJECT ; 
 int GTO ; 
 int PATHSIZE ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  puthead (struct header*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rm (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* tmpdir ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

FILE *
infix(struct header *hp, FILE *fi)
{
	FILE *nfo, *nfi;
	int c, fd;
	char tempname[PATHSIZE];

	(void)snprintf(tempname, sizeof(tempname),
	    "%s/mail.RsXXXXXXXXXX", tmpdir);
	if ((fd = mkstemp(tempname)) == -1 ||
	    (nfo = Fdopen(fd, "w")) == NULL) {
		warn("%s", tempname);
		return (fi);
	}
	if ((nfi = Fopen(tempname, "r")) == NULL) {
		warn("%s", tempname);
		(void)Fclose(nfo);
		(void)rm(tempname);
		return (fi);
	}
	(void)rm(tempname);
	(void)puthead(hp, nfo,
	    GTO|GSUBJECT|GCC|GBCC|GREPLYTO|GINREPLYTO|GNL|GCOMMA);
	c = getc(fi);
	while (c != EOF) {
		(void)putc(c, nfo);
		c = getc(fi);
	}
	if (ferror(fi)) {
		warnx("read");
		rewind(fi);
		return (fi);
	}
	(void)fflush(nfo);
	if (ferror(nfo)) {
		warn("%s", tempname);
		(void)Fclose(nfo);
		(void)Fclose(nfi);
		rewind(fi);
		return (fi);
	}
	(void)Fclose(nfo);
	(void)Fclose(fi);
	rewind(nfi);
	return (nfi);
}