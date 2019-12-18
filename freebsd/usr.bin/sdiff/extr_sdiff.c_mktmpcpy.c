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
typedef  int /*<<< orphan*/  u_char ;
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUFSIZ ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int STDIN_FILENO ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int fstat (int,struct stat*) ; 
 int mkstemp (char*) ; 
 int open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read (int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  tmpdir ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int write (int,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static char *
mktmpcpy(const char *source_file)
{
	struct stat sb;
	ssize_t rcount;
	int ifd, ofd;
	u_char buf[BUFSIZ];
	char *target_file;

	/* Open input and output. */
	ifd = open(source_file, O_RDONLY, 0);
	/* File was opened successfully. */
	if (ifd != -1) {
		if (fstat(ifd, &sb) == -1)
			err(2, "error getting file status from %s", source_file);

		/* Regular file. */
		if (S_ISREG(sb.st_mode)) {
			close(ifd);
			return (NULL);
		}
	} else {
		/* If ``-'' does not exist the user meant stdin. */
		if (errno == ENOENT && strcmp(source_file, "-") == 0)
			ifd = STDIN_FILENO;
		else
			err(2, "error opening %s", source_file);
	}

	/* Not a regular file, so copy input into temporary file. */
	if (asprintf(&target_file, "%s/sdiff.XXXXXXXXXX", tmpdir) == -1)
		err(2, "asprintf");
	if ((ofd = mkstemp(target_file)) == -1) {
		warn("error opening %s", target_file);
		goto FAIL;
	}
	while ((rcount = read(ifd, buf, sizeof(buf))) != -1 &&
	    rcount != 0) {
		ssize_t wcount;

		wcount = write(ofd, buf, (size_t)rcount);
		if (-1 == wcount || rcount != wcount) {
			warn("error writing to %s", target_file);
			goto FAIL;
		}
	}
	if (rcount == -1) {
		warn("error reading from %s", source_file);
		goto FAIL;
	}

	close(ifd);
	close(ofd);

	return (target_file);

FAIL:
	unlink(target_file);
	exit(2);
}