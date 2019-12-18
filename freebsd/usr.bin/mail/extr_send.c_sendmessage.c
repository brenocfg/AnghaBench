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
struct message {long m_size; } ;
struct ignoretab {int dummy; } ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int LINESIZE ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 struct ignoretab* ignoreall ; 
 scalar_t__ isign (char*,struct ignoretab*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int putc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setinput (struct message*) ; 
 int /*<<< orphan*/  statusput (struct message*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int strlen (char*) ; 

int
sendmessage(struct message *mp, FILE *obuf, struct ignoretab *doign,
	char *prefix)
{
	long count;
	FILE *ibuf;
	char *cp, *cp2, line[LINESIZE];
	int ishead, infld, ignoring, dostat, firstline;
	int c = 0, length, prefixlen;

	/*
	 * Compute the prefix string, without trailing whitespace
	 */
	if (prefix != NULL) {
		cp2 = 0;
		for (cp = prefix; *cp != '\0'; cp++)
			if (*cp != ' ' && *cp != '\t')
				cp2 = cp;
		prefixlen = cp2 == NULL ? 0 : cp2 - prefix + 1;
	}
	ibuf = setinput(mp);
	count = mp->m_size;
	ishead = 1;
	dostat = doign == 0 || !isign("status", doign);
	infld = 0;
	firstline = 1;
	/*
	 * Process headers first
	 */
	while (count > 0 && ishead) {
		if (fgets(line, sizeof(line), ibuf) == NULL)
			break;
		count -= length = strlen(line);
		if (firstline) {
			/*
			 * First line is the From line, so no headers
			 * there to worry about
			 */
			firstline = 0;
			ignoring = doign == ignoreall;
		} else if (line[0] == '\n') {
			/*
			 * If line is blank, we've reached end of
			 * headers, so force out status: field
			 * and note that we are no longer in header
			 * fields
			 */
			if (dostat) {
				statusput(mp, obuf, prefix);
				dostat = 0;
			}
			ishead = 0;
			ignoring = doign == ignoreall;
		} else if (infld && (line[0] == ' ' || line[0] == '\t')) {
			/*
			 * If this line is a continuation (via space or tab)
			 * of a previous header field, just echo it
			 * (unless the field should be ignored).
			 * In other words, nothing to do.
			 */
		} else {
			/*
			 * Pick up the header field if we have one.
			 */
			for (cp = line; (c = *cp++) != '\0' && c != ':' &&
			    !isspace((unsigned char)c);)
				;
			cp2 = --cp;
			while (isspace((unsigned char)*cp++))
				;
			if (cp[-1] != ':') {
				/*
				 * Not a header line, force out status:
				 * This happens in uucp style mail where
				 * there are no headers at all.
				 */
				if (dostat) {
					statusput(mp, obuf, prefix);
					dostat = 0;
				}
				if (doign != ignoreall)
					/* add blank line */
					(void)putc('\n', obuf);
				ishead = 0;
				ignoring = 0;
			} else {
				/*
				 * If it is an ignored field and
				 * we care about such things, skip it.
				 */
				*cp2 = '\0';	/* temporarily null terminate */
				if (doign && isign(line, doign))
					ignoring = 1;
				else if ((line[0] == 's' || line[0] == 'S') &&
					 strcasecmp(line, "status") == 0) {
					/*
					 * If the field is "status," go compute
					 * and print the real Status: field
					 */
					if (dostat) {
						statusput(mp, obuf, prefix);
						dostat = 0;
					}
					ignoring = 1;
				} else {
					ignoring = 0;
					*cp2 = c;	/* restore */
				}
				infld = 1;
			}
		}
		if (!ignoring) {
			/*
			 * Strip trailing whitespace from prefix
			 * if line is blank.
			 */
			if (prefix != NULL) {
				if (length > 1)
					fputs(prefix, obuf);
				else
					(void)fwrite(prefix, sizeof(*prefix),
					    prefixlen, obuf);
			}
			(void)fwrite(line, sizeof(*line), length, obuf);
			if (ferror(obuf))
				return (-1);
		}
	}
	/*
	 * Copy out message body
	 */
	if (doign == ignoreall)
		count--;		/* skip final blank line */
	if (prefix != NULL)
		while (count > 0) {
			if (fgets(line, sizeof(line), ibuf) == NULL) {
				c = 0;
				break;
			}
			count -= c = strlen(line);
			/*
			 * Strip trailing whitespace from prefix
			 * if line is blank.
			 */
			if (c > 1)
				fputs(prefix, obuf);
			else
				(void)fwrite(prefix, sizeof(*prefix),
				    prefixlen, obuf);
			(void)fwrite(line, sizeof(*line), c, obuf);
			if (ferror(obuf))
				return (-1);
		}
	else
		while (count > 0) {
			c = count < LINESIZE ? count : LINESIZE;
			if ((c = fread(line, sizeof(*line), c, ibuf)) <= 0)
				break;
			count -= c;
			if (fwrite(line, sizeof(*line), c, obuf) != c)
				return (-1);
		}
	if (doign == ignoreall && c > 0 && line[c - 1] != '\n')
		/* no final blank line */
		if ((c = getc(ibuf)) != EOF && putc(c, obuf) == EOF)
			return (-1);
	return (0);
}