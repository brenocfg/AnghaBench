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
struct label_spec_entry {char* regexstr; char* mactext; char* modestr; int /*<<< orphan*/  mode; int /*<<< orphan*/  flags; int /*<<< orphan*/  regex; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_DONTLABEL ; 
 int REG_EXTENDED ; 
 int REG_NOSUB ; 
 int /*<<< orphan*/  S_IFBLK ; 
 int /*<<< orphan*/  S_IFCHR ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  S_IFIFO ; 
 int /*<<< orphan*/  S_IFLNK ; 
 int /*<<< orphan*/  S_IFREG ; 
 int /*<<< orphan*/  S_IFSOCK ; 
 int asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,char const*,...) ; 
 char* malloc (size_t) ; 
 int regcomp (int /*<<< orphan*/ *,char*,int) ; 
 size_t regerror (int,int /*<<< orphan*/ *,char*,size_t) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 char* strtok (char*,char*) ; 

void
add_spec_line(const char *file, int is_sebsd, struct label_spec_entry *entry,
    char *line)
{
	char *regexstr, *modestr, *macstr, *regerrorstr;
	size_t size;
	int error;

	regexstr = strtok(line, " \t");
	if (regexstr == NULL)
		errx(1, "%s: need regular expression", file);
	modestr = strtok(NULL, " \t");
	if (modestr == NULL)
		errx(1, "%s: need a label", file);
	macstr = strtok(NULL, " \t");
	if (macstr == NULL) {	/* the mode is just optional */
		macstr = modestr;
		modestr = NULL;
	}
	if (strtok(NULL, " \t") != NULL)
		errx(1, "%s: extraneous fields at end of line", file);
	/* assume we need to anchor this regex */
	if (asprintf(&regexstr, "^%s$", regexstr) == -1)
		err(1, "%s: processing regular expression", file);
	entry->regexstr = regexstr;
	error = regcomp(&entry->regex, regexstr, REG_EXTENDED | REG_NOSUB);
	if (error) {
		size = regerror(error, &entry->regex, NULL, 0);
		regerrorstr = malloc(size);
		if (regerrorstr == NULL)
			err(1, "malloc");
		(void)regerror(error, &entry->regex, regerrorstr, size);
		errx(1, "%s: %s: %s", file, entry->regexstr, regerrorstr);
	}
	if (!is_sebsd) {
		entry->mactext = strdup(macstr);
		if (entry->mactext == NULL)
			err(1, "strdup");
	} else {
		if (asprintf(&entry->mactext, "sebsd/%s", macstr) == -1)
			err(1, "asprintf");
		if (strcmp(macstr, "<<none>>") == 0)
			entry->flags |= F_DONTLABEL;
	}
	if (modestr != NULL) {
		if (strlen(modestr) != 2 || modestr[0] != '-')
			errx(1, "%s: invalid mode string: %s", file, modestr);
		switch (modestr[1]) {
		case 'b':
			entry->mode = S_IFBLK;
			entry->modestr = ",-b";
			break;
		case 'c':
			entry->mode = S_IFCHR;
			entry->modestr = ",-c";
			break;
		case 'd':
			entry->mode = S_IFDIR;
			entry->modestr = ",-d";
			break;
		case 'p':
			entry->mode = S_IFIFO;
			entry->modestr = ",-p";
			break;
		case 'l':
			entry->mode = S_IFLNK;
			entry->modestr = ",-l";
			break;
		case 's':
			entry->mode = S_IFSOCK;
			entry->modestr = ",-s";
			break;
		case '-':
			entry->mode = S_IFREG;
			entry->modestr = ",--";
			break;
		default:
			errx(1, "%s: invalid mode string: %s", file, modestr);
		}
	} else {
		entry->modestr = "";
	}
}