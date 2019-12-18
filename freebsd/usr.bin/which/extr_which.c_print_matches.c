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
typedef  int /*<<< orphan*/  candidate ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  allpaths ; 
 scalar_t__ is_there (char*) ; 
 int snprintf (char*,int,char*,char const*,char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
print_matches(char *path, char *filename)
{
	char candidate[PATH_MAX];
	const char *d;
	int found;

	if (strchr(filename, '/') != NULL)
		return (is_there(filename) ? 0 : -1);
	found = 0;
	while ((d = strsep(&path, ":")) != NULL) {
		if (*d == '\0')
			d = ".";
		if (snprintf(candidate, sizeof(candidate), "%s/%s", d,
		    filename) >= (int)sizeof(candidate))
			continue;
		if (is_there(candidate)) {
			found = 1;
			if (!allpaths)
				break;
		}
	}
	return (found ? 0 : -1);
}