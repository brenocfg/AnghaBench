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
 scalar_t__ EOF ; 
 int /*<<< orphan*/  MANDOCERR_FDOPEN ; 
 int /*<<< orphan*/  MANDOCERR_FFLUSH ; 
 int /*<<< orphan*/  MANDOCERR_GETLINE ; 
 int /*<<< orphan*/  MANDOCERR_WRITE ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 scalar_t__ fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
passthrough(int fd, int synopsis_only)
{
	const char	 synb[] = "S\bSY\bYN\bNO\bOP\bPS\bSI\bIS\bS";
	const char	 synr[] = "SYNOPSIS";

	FILE		*stream;
	char		*line, *cp;
	size_t		 linesz;
	ssize_t		 len, written;
	int		 lno, print;

	stream = NULL;
	line = NULL;
	linesz = 0;

	if (fflush(stdout) == EOF) {
		mandoc_msg(MANDOCERR_FFLUSH, 0, 0, "%s", strerror(errno));
		goto done;
	}
	if ((stream = fdopen(fd, "r")) == NULL) {
		close(fd);
		mandoc_msg(MANDOCERR_FDOPEN, 0, 0, "%s", strerror(errno));
		goto done;
	}

	lno = print = 0;
	while ((len = getline(&line, &linesz, stream)) != -1) {
		lno++;
		cp = line;
		if (synopsis_only) {
			if (print) {
				if ( ! isspace((unsigned char)*cp))
					goto done;
				while (isspace((unsigned char)*cp)) {
					cp++;
					len--;
				}
			} else {
				if (strcmp(cp, synb) == 0 ||
				    strcmp(cp, synr) == 0)
					print = 1;
				continue;
			}
		}
		for (; len > 0; len -= written) {
			if ((written = write(STDOUT_FILENO, cp, len)) == -1) {
				mandoc_msg(MANDOCERR_WRITE, 0, 0,
				    "%s", strerror(errno));
				goto done;
			}
		}
	}
	if (ferror(stream))
		mandoc_msg(MANDOCERR_GETLINE, lno, 0, "%s", strerror(errno));

done:
	free(line);
	if (stream != NULL)
		fclose(stream);
}