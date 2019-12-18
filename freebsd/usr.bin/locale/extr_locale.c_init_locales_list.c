#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dirent {char* d_name; } ;
struct TYPE_5__ {int /*<<< orphan*/  sl_cur; int /*<<< orphan*/  sl_str; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 size_t NBOGUS ; 
 int /*<<< orphan*/  _PathLocale ; 
 scalar_t__ __detect_path_locale () ; 
 int /*<<< orphan*/ * boguslocales ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 TYPE_1__* locales ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scmp ; 
 int /*<<< orphan*/  sl_add (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sl_find (TYPE_1__*,char*) ; 
 TYPE_1__* sl_init () ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
init_locales_list(void)
{
	DIR *dirp;
	struct dirent *dp;
	size_t i;
	int bogus;

	/* why call this function twice ? */
	if (locales != NULL)
		return;

	/* initialize StringList */
	locales = sl_init();
	if (locales == NULL)
		err(1, "could not allocate memory");

	/* get actual locales directory name */
	if (__detect_path_locale() != 0)
		err(1, "unable to find locales storage");

	/* open locales directory */
	dirp = opendir(_PathLocale);
	if (dirp == NULL)
		err(1, "could not open directory '%s'", _PathLocale);

	/* scan directory and store its contents except "." and ".." */
	while ((dp = readdir(dirp)) != NULL) {
		if (*(dp->d_name) == '.')
			continue;		/* exclude "." and ".." */
		for (bogus = i = 0; i < NBOGUS; i++)
			if (strncmp(dp->d_name, boguslocales[i],
			    strlen(boguslocales[i])) == 0)
				bogus = 1;
		if (!bogus)
			sl_add(locales, strdup(dp->d_name));
	}
	closedir(dirp);

	/* make sure that 'POSIX' and 'C' locales are present in the list.
	 * POSIX 1003.1-2001 requires presence of 'POSIX' name only here, but
	 * we also list 'C' for constistency
	 */
	if (sl_find(locales, "POSIX") == NULL)
		sl_add(locales, strdup("POSIX"));

	if (sl_find(locales, "C") == NULL)
		sl_add(locales, strdup("C"));

	/* make output nicer, sort the list */
	qsort(locales->sl_str, locales->sl_cur, sizeof(char *), scmp);
}