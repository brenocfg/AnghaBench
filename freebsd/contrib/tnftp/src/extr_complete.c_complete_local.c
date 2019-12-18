#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; size_t d_namlen; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  dir ;
struct TYPE_6__ {char** sl_str; } ;
typedef  TYPE_1__ StringList ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 unsigned char CC_ERROR ; 
 unsigned char CC_REFRESH ; 
 int MAXPATHLEN ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 unsigned char complete_ambiguous (char*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  el ; 
 int el_insertstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ftp_sl_add (TYPE_1__*,char*) ; 
 TYPE_1__* ftp_sl_init () ; 
 char* ftp_strdup (char*) ; 
 char* globulize (char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sl_free (TYPE_1__*,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,size_t) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static unsigned char
complete_local(char *word, int list)
{
	StringList *words;
	char dir[MAXPATHLEN];
	char *file;
	DIR *dd;
	struct dirent *dp;
	unsigned char rv;
	size_t len;

	if ((file = strrchr(word, '/')) == NULL) {
		dir[0] = '.';
		dir[1] = '\0';
		file = word;
	} else {
		if (file == word) {
			dir[0] = '/';
			dir[1] = '\0';
		} else
			(void)strlcpy(dir, word, file - word + 1);
		file++;
	}
	if (dir[0] == '~') {
		char *p;

		if ((p = globulize(dir)) == NULL)
			return (CC_ERROR);
		(void)strlcpy(dir, p, sizeof(dir));
		free(p);
	}

	if ((dd = opendir(dir)) == NULL)
		return (CC_ERROR);

	words = ftp_sl_init();
	len = strlen(file);

	for (dp = readdir(dd); dp != NULL; dp = readdir(dd)) {
		if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
			continue;

#if defined(DIRENT_MISSING_D_NAMLEN)
		if (len > strlen(dp->d_name))
			continue;
#else
		if (len > dp->d_namlen)
			continue;
#endif
		if (strncmp(file, dp->d_name, len) == 0) {
			char *tcp;

			tcp = ftp_strdup(dp->d_name);
			ftp_sl_add(words, tcp);
		}
	}
	closedir(dd);

	rv = complete_ambiguous(file, list, words);
	if (rv == CC_REFRESH) {
		struct stat sb;
		char path[MAXPATHLEN];

		(void)strlcpy(path, dir,		sizeof(path));
		(void)strlcat(path, "/",		sizeof(path));
		(void)strlcat(path, words->sl_str[0],	sizeof(path));

		if (stat(path, &sb) >= 0) {
			char suffix[2] = " ";

			if (S_ISDIR(sb.st_mode))
				suffix[0] = '/';
			if (el_insertstr(el, suffix) == -1)
				rv = CC_ERROR;
		}
	}
	sl_free(words, 1);
	return (rv);
}