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
 char* el_calloc (size_t,int) ; 
 int /*<<< orphan*/  el_free (char**) ; 
 char** el_realloc (char**,size_t) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 char* stub1 (char const*,int) ; 

char **
completion_matches(const char *text, char *(*genfunc)(const char *, int))
{
	char **match_list = NULL, *retstr, *prevstr;
	size_t match_list_len, max_equal, which, i;
	size_t matches;

	matches = 0;
	match_list_len = 1;
	while ((retstr = (*genfunc) (text, (int)matches)) != NULL) {
		/* allow for list terminator here */
		if (matches + 3 >= match_list_len) {
			char **nmatch_list;
			while (matches + 3 >= match_list_len)
				match_list_len <<= 1;
			nmatch_list = el_realloc(match_list,
			    match_list_len * sizeof(*nmatch_list));
			if (nmatch_list == NULL) {
				el_free(match_list);
				return NULL;
			}
			match_list = nmatch_list;

		}
		match_list[++matches] = retstr;
	}

	if (!match_list)
		return NULL;	/* nothing found */

	/* find least denominator and insert it to match_list[0] */
	which = 2;
	prevstr = match_list[1];
	max_equal = strlen(prevstr);
	for (; which <= matches; which++) {
		for (i = 0; i < max_equal &&
		    prevstr[i] == match_list[which][i]; i++)
			continue;
		max_equal = i;
	}

	retstr = el_calloc(max_equal + 1, sizeof(*retstr));
	if (retstr == NULL) {
		el_free(match_list);
		return NULL;
	}
	(void)strncpy(retstr, match_list[1], max_equal);
	retstr[max_equal] = '\0';
	match_list[0] = retstr;

	/* add NULL as last pointer to the array */
	match_list[matches + 1] = NULL;

	return match_list;
}