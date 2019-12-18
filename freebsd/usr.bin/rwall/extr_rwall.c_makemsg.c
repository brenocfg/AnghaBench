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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  tmpname ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_hour; int tm_min; } ;
struct stat {scalar_t__ st_size; } ;
struct passwd {char* pw_name; } ;
typedef  int /*<<< orphan*/  lbuf ;
typedef  int /*<<< orphan*/  hostname ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 char* _PATH_TMP ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ fread (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freopen (char const*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 char* getlogin () ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/ * mbuf ; 
 int mkstemp (char*) ; 
 char* notty ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 char* ttyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void
makemsg(const char *fname)
{
	struct tm *lt;
	struct passwd *pw;
	struct stat sbuf;
	time_t now;
	FILE *fp;
	int fd;
	size_t mbufsize;
	char *tty, hostname[MAXHOSTNAMELEN], lbuf[256], tmpname[64];
	const char *whom;

	snprintf(tmpname, sizeof(tmpname), "%s/wall.XXXXXX", _PATH_TMP);
	if ((fd = mkstemp(tmpname)) == -1 || (fp = fdopen(fd, "r+")) == NULL)
		err(1, "can't open temporary file");
	unlink(tmpname);

	whom = getlogin();
	if (!whom) {
		pw = getpwuid(getuid());
		whom = pw ? pw->pw_name : "???";
	}
	gethostname(hostname, sizeof(hostname));
	time(&now);
	lt = localtime(&now);

	/*
	 * all this stuff is to blank out a square for the message;
	 * we wrap message lines at column 79, not 80, because some
	 * terminals wrap after 79, some do not, and we can't tell.
	 * Which means that we may leave a non-blank character
	 * in column 80, but that can't be helped.
	 */
	fprintf(fp, "Remote Broadcast Message from %s@%s\n",
	    whom, hostname);
	tty = ttyname(STDERR_FILENO);
	if (tty == NULL)
		tty = notty;
	fprintf(fp, "        (%s) at %d:%02d ...\n", tty,
	    lt->tm_hour, lt->tm_min);

	putc('\n', fp);

	if (fname && !(freopen(fname, "r", stdin)))
		err(1, "can't read %s", fname);
	while (fgets(lbuf, sizeof(lbuf), stdin))
		fputs(lbuf, fp);
	rewind(fp);

	if (fstat(fd, &sbuf))
		err(1, "can't stat temporary file");
	mbufsize = (size_t)sbuf.st_size;
	mbuf = malloc(mbufsize);
	if (mbuf == NULL)
		err(1, "out of memory");
	if (fread(mbuf, sizeof(*mbuf), mbufsize, fp) != (u_int)mbufsize)
		err(1, "can't read temporary file");
	close(fd);
}