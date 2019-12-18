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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int NS_SUCCESS ; 
 int NS_UNAVAIL ; 
 int /*<<< orphan*/  _PATH_SHELLS ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isspace (char) ; 
 scalar_t__ sl ; 
 int /*<<< orphan*/  sl_add (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_free (scalar_t__,int) ; 
 scalar_t__ sl_init () ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static int
_local_initshells(void	*rv, void *cb_data, va_list ap)
{
	char	*sp, *cp;
	FILE	*fp;
	char	 line[MAXPATHLEN + 2];

	if (sl)
		sl_free(sl, 1);
	sl = sl_init();

	if ((fp = fopen(_PATH_SHELLS, "re")) == NULL)
		return NS_UNAVAIL;

	while (fgets(line, MAXPATHLEN + 1, fp) != NULL) {
		cp = line;
		while (*cp != '#' && *cp != '/' && *cp != '\0')
			cp++;
		if (*cp == '#' || *cp == '\0')
			continue;
		sp = cp;
		while (!isspace(*cp) && *cp != '#' && *cp != '\0')
			cp++;
		*cp = '\0';
		sl_add(sl, strdup(sp));
	}
	(void)fclose(fp);
	return NS_SUCCESS;
}