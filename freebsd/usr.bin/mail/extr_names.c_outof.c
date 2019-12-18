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
typedef  int /*<<< orphan*/  tempname ;
struct name {char* n_name; struct name* n_flink; int /*<<< orphan*/  n_type; } ;
struct header {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  Fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Fdopen (int,char*) ; 
 int /*<<< orphan*/ * Fopen (char*,char*) ; 
 int GCC ; 
 int /*<<< orphan*/  GDEL ; 
 int GINREPLYTO ; 
 int GNL ; 
 int GREPLYTO ; 
 int GSUBJECT ; 
 int GTO ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PATHSIZE ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 char* _PATH_CSHELL ; 
 int /*<<< orphan*/  close (int) ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 int dup (int) ; 
 char* expand (char*) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free_child (int) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int image ; 
 int /*<<< orphan*/  isfileaddr (char*) ; 
 int mkstemp (char*) ; 
 char* myname ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  puthead (struct header*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rm (char*) ; 
 int /*<<< orphan*/  senderr ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int start_command (char*,int /*<<< orphan*/ *,int,int,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 char* tmpdir ; 
 char* value (char*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

struct name *
outof(struct name *names, FILE *fo, struct header *hp)
{
	int c, ispipe;
	struct name *np, *top;
	time_t now;
	char *date, *fname;
	FILE *fout, *fin;

	top = names;
	np = names;
	(void)time(&now);
	date = ctime(&now);
	while (np != NULL) {
		if (!isfileaddr(np->n_name) && np->n_name[0] != '|') {
			np = np->n_flink;
			continue;
		}
		ispipe = np->n_name[0] == '|';
		if (ispipe)
			fname = np->n_name+1;
		else
			fname = expand(np->n_name);

		/*
		 * See if we have copied the complete message out yet.
		 * If not, do so.
		 */

		if (image < 0) {
			int fd;
			char tempname[PATHSIZE];

			(void)snprintf(tempname, sizeof(tempname),
			    "%s/mail.ReXXXXXXXXXX", tmpdir);
			if ((fd = mkstemp(tempname)) == -1 ||
			    (fout = Fdopen(fd, "a")) == NULL) {
				warn("%s", tempname);
				senderr++;
				goto cant;
			}
			image = open(tempname, O_RDWR);
			(void)rm(tempname);
			if (image < 0) {
				warn("%s", tempname);
				senderr++;
				(void)Fclose(fout);
				goto cant;
			}
			(void)fcntl(image, F_SETFD, 1);
			fprintf(fout, "From %s %s", myname, date);
			puthead(hp, fout,
			    GTO|GSUBJECT|GCC|GREPLYTO|GINREPLYTO|GNL);
			while ((c = getc(fo)) != EOF)
				(void)putc(c, fout);
			rewind(fo);
			fprintf(fout, "\n");
			(void)fflush(fout);
			if (ferror(fout)) {
				warn("%s", tempname);
				senderr++;
				(void)Fclose(fout);
				goto cant;
			}
			(void)Fclose(fout);
		}

		/*
		 * Now either copy "image" to the desired file
		 * or give it as the standard input to the desired
		 * program as appropriate.
		 */

		if (ispipe) {
			int pid;
			char *sh;
			sigset_t nset;

			/*
			 * XXX
			 * We can't really reuse the same image file,
			 * because multiple piped recipients will
			 * share the same lseek location and trample
			 * on one another.
			 */
			if ((sh = value("SHELL")) == NULL)
				sh = _PATH_CSHELL;
			(void)sigemptyset(&nset);
			(void)sigaddset(&nset, SIGHUP);
			(void)sigaddset(&nset, SIGINT);
			(void)sigaddset(&nset, SIGQUIT);
			pid = start_command(sh, &nset, image, -1, "-c", fname,
			    NULL);
			if (pid < 0) {
				senderr++;
				goto cant;
			}
			free_child(pid);
		} else {
			int f;
			if ((fout = Fopen(fname, "a")) == NULL) {
				warn("%s", fname);
				senderr++;
				goto cant;
			}
			if ((f = dup(image)) < 0) {
				warn("dup");
				fin = NULL;
			} else
				fin = Fdopen(f, "r");
			if (fin == NULL) {
				fprintf(stderr, "Can't reopen image\n");
				(void)Fclose(fout);
				senderr++;
				goto cant;
			}
			rewind(fin);
			while ((c = getc(fin)) != EOF)
				(void)putc(c, fout);
			if (ferror(fout)) {
				warnx("%s", fname);
				senderr++;
				(void)Fclose(fout);
				(void)Fclose(fin);
				goto cant;
			}
			(void)Fclose(fout);
			(void)Fclose(fin);
		}
cant:
		/*
		 * In days of old we removed the entry from the
		 * the list; now for sake of header expansion
		 * we leave it in and mark it as deleted.
		 */
		np->n_type |= GDEL;
		np = np->n_flink;
	}
	if (image >= 0) {
		(void)close(image);
		image = -1;
	}
	return (top);
}