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
struct mpage {char* sec; void* desc; struct mlink* mlinks; } ;
struct mlink {char* dsec; int /*<<< orphan*/  file; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (unsigned char) ; 
 char* mandoc_realloc (char*,size_t) ; 
 void* mandoc_strndup (char*,int) ; 
 char* memchr (char*,char,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  say (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char*) ; 
 char* strstr (char*,char*) ; 
 scalar_t__ warnings ; 

__attribute__((used)) static void
parse_cat(struct mpage *mpage, int fd)
{
	FILE		*stream;
	struct mlink	*mlink;
	char		*line, *p, *title, *sec;
	size_t		 linesz, plen, titlesz;
	ssize_t		 len;
	int		 offs;

	mlink = mpage->mlinks;
	stream = fd == -1 ? fopen(mlink->file, "r") : fdopen(fd, "r");
	if (stream == NULL) {
		if (fd != -1)
			close(fd);
		if (warnings)
			say(mlink->file, "&fopen");
		return;
	}

	line = NULL;
	linesz = 0;

	/* Parse the section number from the header line. */

	while (getline(&line, &linesz, stream) != -1) {
		if (*line == '\n')
			continue;
		if ((sec = strchr(line, '(')) == NULL)
			break;
		if ((p = strchr(++sec, ')')) == NULL)
			break;
		free(mpage->sec);
		mpage->sec = mandoc_strndup(sec, p - sec);
		if (warnings && *mlink->dsec != '\0' &&
		    strcasecmp(mpage->sec, mlink->dsec))
			say(mlink->file,
			    "Section \"%s\" manual in %s directory",
			    mpage->sec, mlink->dsec);
		break;
	}

	/* Skip to first blank line. */

	while (line == NULL || *line != '\n')
		if (getline(&line, &linesz, stream) == -1)
			break;

	/*
	 * Assume the first line that is not indented
	 * is the first section header.  Skip to it.
	 */

	while (getline(&line, &linesz, stream) != -1)
		if (*line != '\n' && *line != ' ')
			break;

	/*
	 * Read up until the next section into a buffer.
	 * Strip the leading and trailing newline from each read line,
	 * appending a trailing space.
	 * Ignore empty (whitespace-only) lines.
	 */

	titlesz = 0;
	title = NULL;

	while ((len = getline(&line, &linesz, stream)) != -1) {
		if (*line != ' ')
			break;
		offs = 0;
		while (isspace((unsigned char)line[offs]))
			offs++;
		if (line[offs] == '\0')
			continue;
		title = mandoc_realloc(title, titlesz + len - offs);
		memcpy(title + titlesz, line + offs, len - offs);
		titlesz += len - offs;
		title[titlesz - 1] = ' ';
	}
	free(line);

	/*
	 * If no page content can be found, or the input line
	 * is already the next section header, or there is no
	 * trailing newline, reuse the page title as the page
	 * description.
	 */

	if (NULL == title || '\0' == *title) {
		if (warnings)
			say(mlink->file, "Cannot find NAME section");
		fclose(stream);
		free(title);
		return;
	}

	title[titlesz - 1] = '\0';

	/*
	 * Skip to the first dash.
	 * Use the remaining line as the description (no more than 70
	 * bytes).
	 */

	if (NULL != (p = strstr(title, "- "))) {
		for (p += 2; ' ' == *p || '\b' == *p; p++)
			/* Skip to next word. */ ;
	} else {
		if (warnings)
			say(mlink->file, "No dash in title line, "
			    "reusing \"%s\" as one-line description", title);
		p = title;
	}

	plen = strlen(p);

	/* Strip backspace-encoding from line. */

	while (NULL != (line = memchr(p, '\b', plen))) {
		len = line - p;
		if (0 == len) {
			memmove(line, line + 1, plen--);
			continue;
		}
		memmove(line - 1, line + 1, plen - len);
		plen -= 2;
	}

	/*
	 * Cut off excessive one-line descriptions.
	 * Bad pages are not worth better heuristics.
	 */

	mpage->desc = mandoc_strndup(p, 150);
	fclose(stream);
	free(title);
}