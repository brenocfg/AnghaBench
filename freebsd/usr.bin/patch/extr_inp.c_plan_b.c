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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t BUFFERSIZE ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 char const* TMPINNAME ; 
 int /*<<< orphan*/  ask (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ batch ; 
 char* buf ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * fgets (char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ force ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 size_t input_lines ; 
 int last_line_missing_eol ; 
 size_t lines_per_buf ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  open (char const*,int,...) ; 
 int /*<<< orphan*/  pfatal (char*,...) ; 
 scalar_t__ rev_in_string (char*) ; 
 int /*<<< orphan*/ * revision ; 
 int /*<<< orphan*/  say (char*,int /*<<< orphan*/ *) ; 
 size_t strlen (char*) ; 
 char** tibuf ; 
 size_t tibuflen ; 
 int /*<<< orphan*/  tifd ; 
 size_t tireclen ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 int using_plan_a ; 
 scalar_t__ verbose ; 
 scalar_t__ write (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static void
plan_b(const char *filename)
{
	FILE	*ifp;
	size_t	i = 0, j, len, maxlen = 1;
	char	*lbuf = NULL, *p;
	bool	found_revision = (revision == NULL);

	using_plan_a = false;
	if ((ifp = fopen(filename, "r")) == NULL)
		pfatal("can't open file %s", filename);
	unlink(TMPINNAME);
	if ((tifd = open(TMPINNAME, O_EXCL | O_CREAT | O_WRONLY, 0666)) < 0)
		pfatal("can't open file %s", TMPINNAME);
	while ((p = fgetln(ifp, &len)) != NULL) {
		if (p[len - 1] == '\n')
			p[len - 1] = '\0';
		else {
			/* EOF without EOL, copy and add the NUL */
			if ((lbuf = malloc(len + 1)) == NULL)
				fatal("out of memory\n");
			memcpy(lbuf, p, len);
			lbuf[len] = '\0';
			p = lbuf;

			last_line_missing_eol = true;
			len++;
		}
		if (revision != NULL && !found_revision && rev_in_string(p))
			found_revision = true;
		if (len > maxlen)
			maxlen = len;   /* find longest line */
	}
	free(lbuf);
	if (ferror(ifp))
		pfatal("can't read file %s", filename);

	if (revision != NULL) {
		if (!found_revision) {
			if (force) {
				if (verbose)
					say("Warning: this file doesn't appear "
					    "to be the %s version--patching anyway.\n",
					    revision);
			} else if (batch) {
				fatal("this file doesn't appear to be the "
				    "%s version--aborting.\n",
				    revision);
			} else {
				ask("This file doesn't appear to be the %s "
				    "version--patch anyway? [n] ",
				    revision);
				if (*buf != 'y')
					fatal("aborted\n");
			}
		} else if (verbose)
			say("Good.  This file appears to be the %s version.\n",
			    revision);
	}
	fseek(ifp, 0L, SEEK_SET);	/* rewind file */
	tireclen = maxlen;
	tibuflen = maxlen > BUFFERSIZE ? maxlen : BUFFERSIZE;
	lines_per_buf = tibuflen / maxlen;
	tibuf[0] = malloc(tibuflen + 1);
	if (tibuf[0] == NULL)
		fatal("out of memory\n");
	tibuf[1] = malloc(tibuflen + 1);
	if (tibuf[1] == NULL)
		fatal("out of memory\n");
	for (i = 1;; i++) {
		p = tibuf[0] + maxlen * (i % lines_per_buf);
		if (i % lines_per_buf == 0)	/* new block */
			if (write(tifd, tibuf[0], tibuflen) !=
			    (ssize_t) tibuflen)
				pfatal("can't write temp file");
		if (fgets(p, maxlen + 1, ifp) == NULL) {
			input_lines = i - 1;
			if (i % lines_per_buf != 0)
				if (write(tifd, tibuf[0], tibuflen) !=
				    (ssize_t) tibuflen)
					pfatal("can't write temp file");
			break;
		}
		j = strlen(p);
		/* These are '\n' terminated strings, so no need to add a NUL */
		if (j == 0 || p[j - 1] != '\n')
			p[j] = '\n';
	}
	fclose(ifp);
	close(tifd);
	if ((tifd = open(TMPINNAME, O_RDONLY)) < 0)
		pfatal("can't reopen file %s", TMPINNAME);
}