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
 char* checked_strdup (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
login_list_prefers(const char *list,
    const char *choice1, const char *choice2)
{
	char *tofree, *str, *token;

	tofree = str = checked_strdup(list);

	while ((token = strsep(&str, ",")) != NULL) {
		if (strcmp(token, choice1) == 0) {
			free(tofree);
			return (1);
		}
		if (strcmp(token, choice2) == 0) {
			free(tofree);
			return (2);
		}
	}
	free(tofree);
	return (-1);
}