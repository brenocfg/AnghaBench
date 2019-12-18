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
 scalar_t__ strcmp (char*,char const*) ; 
 char* strdup (char const*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
find_token(const char *buffer, const char *token)
{
	char *buffer_tmp, *buffer_copy, *inputstring;
	char **ap;
	int found;

	buffer_copy = strdup(buffer);
	buffer_tmp = buffer_copy;
	inputstring = buffer_copy;
	ap = &buffer_tmp;

	found = 0;

	while ((*ap = strsep(&inputstring, ",")) != NULL) {
		if (strcmp(buffer_tmp, token) == 0) {
			found = 1;
			break;
		}
	}

	free(buffer_copy);

	return found;
}