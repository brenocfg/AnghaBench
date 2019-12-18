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

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int match_pattern_list (char*,char const*,int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int strlen (char const*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static char *
filter_list(const char *proposal, const char *filter, int blacklist)
{
	size_t len = strlen(proposal) + 1;
	char *fix_prop = malloc(len);
	char *orig_prop = strdup(proposal);
	char *cp, *tmp;
	int r;

	if (fix_prop == NULL || orig_prop == NULL) {
		free(orig_prop);
		free(fix_prop);
		return NULL;
	}

	tmp = orig_prop;
	*fix_prop = '\0';
	while ((cp = strsep(&tmp, ",")) != NULL) {
		r = match_pattern_list(cp, filter, 0);
		if ((blacklist && r != 1) || (!blacklist && r == 1)) {
			if (*fix_prop != '\0')
				strlcat(fix_prop, ",", len);
			strlcat(fix_prop, cp, len);
		}
	}
	free(orig_prop);
	return fix_prop;
}