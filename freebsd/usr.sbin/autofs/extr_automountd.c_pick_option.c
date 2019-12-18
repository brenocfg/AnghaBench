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
 char* calloc (int,int) ; 
 char* checked_strdup (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static char *
pick_option(const char *option, char **optionsp)
{
	char *tofree, *pair, *newoptions;
	char *picked = NULL;
	bool first = true;

	tofree = *optionsp;

	newoptions = calloc(1, strlen(*optionsp) + 1);
	if (newoptions == NULL)
		log_err(1, "calloc");

	while ((pair = strsep(optionsp, ",")) != NULL) {
		/*
		 * XXX: strncasecmp(3) perhaps?
		 */
		if (strncmp(pair, option, strlen(option)) == 0) {
			picked = checked_strdup(pair + strlen(option));
		} else {
			if (first == false)
				strcat(newoptions, ",");
			else
				first = false;
			strcat(newoptions, pair);
		}
	}

	free(tofree);
	*optionsp = newoptions;

	return (picked);
}