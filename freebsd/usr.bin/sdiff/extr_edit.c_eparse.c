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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int asprintf (char**,char*,char const*,...) ; 
 int /*<<< orphan*/  cleanup (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int editit (char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t fwrite (char*,int,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (char const) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  outfp ; 
 size_t strlen (char*) ; 
 char const* tmpdir ; 
 scalar_t__ unlink (char*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 
 int write (int,char*,size_t) ; 

int
eparse(const char *cmd, const char *left, const char *right)
{
	FILE *file;
	size_t nread;
	int fd;
	char *filename;
	char buf[BUFSIZ], *text;

	/* Skip whitespace. */
	while (isspace(*cmd))
		++cmd;

	text = NULL;
	switch (*cmd) {
	case '\0':
		/* Edit empty file. */
		break;

	case 'b':
		/* Both strings. */
		if (left == NULL)
			goto RIGHT;
		if (right == NULL)
			goto LEFT;

		/* Neither column is blank, so print both. */
		if (asprintf(&text, "%s\n%s\n", left, right) == -1)
			err(2, "could not allocate memory");
		break;

	case 'l':
LEFT:
		/* Skip if there is no left column. */
		if (left == NULL)
			break;

		if (asprintf(&text, "%s\n", left) == -1)
			err(2, "could not allocate memory");

		break;

	case 'r':
RIGHT:
		/* Skip if there is no right column. */
		if (right == NULL)
			break;

		if (asprintf(&text, "%s\n", right) == -1)
			err(2, "could not allocate memory");

		break;

	default:
		return (-1);
	}

	/* Create temp file. */
	if (asprintf(&filename, "%s/sdiff.XXXXXXXXXX", tmpdir) == -1)
		err(2, "asprintf");
	if ((fd = mkstemp(filename)) == -1)
		err(2, "mkstemp");
	if (text != NULL) {
		size_t len;
		ssize_t nwritten;

		len = strlen(text);
		if ((nwritten = write(fd, text, len)) == -1 ||
		    (size_t)nwritten != len) {
			warn("error writing to temp file");
			cleanup(filename);
		}
	}
	close(fd);

	/* text is no longer used. */
	free(text);

	/* Edit temp file. */
	if (editit(filename) == -1) {
		warn("error editing %s", filename);
		cleanup(filename);
	}

	/* Open temporary file. */
	if (!(file = fopen(filename, "r"))) {
		warn("could not open edited file: %s", filename);
		cleanup(filename);
	}

	/* Copy temporary file contents to output file. */
	for (nread = sizeof(buf); nread == sizeof(buf);) {
		size_t nwritten;

		nread = fread(buf, sizeof(*buf), sizeof(buf), file);
		/* Test for error or end of file. */
		if (nread != sizeof(buf) &&
		    (ferror(file) || !feof(file))) {
			warnx("error reading edited file: %s", filename);
			cleanup(filename);
		}

		/*
		 * If we have nothing to read, break out of loop
		 * instead of writing nothing.
		 */
		if (!nread)
			break;

		/* Write data we just read. */
		nwritten = fwrite(buf, sizeof(*buf), nread, outfp);
		if (nwritten != nread) {
			warnx("error writing to output file");
			cleanup(filename);
		}
	}

	/* We've reached the end of the temporary file, so remove it. */
	if (unlink(filename))
		warn("could not delete: %s", filename);
	fclose(file);

	free(filename);

	return (0);
}