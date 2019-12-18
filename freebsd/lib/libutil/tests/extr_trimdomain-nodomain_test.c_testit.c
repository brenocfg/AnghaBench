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
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 char* strdup (char const*) ; 
 scalar_t__ strlen (char*) ; 
 int tests ; 
 int /*<<< orphan*/  trimdomain (char*,int) ; 

void
testit(const char *input, int hostsize, const char *output, const char *test)
{
	char *testhost;
	const char *expected = (output == NULL) ? input : output;

	testhost = strdup(input);
	trimdomain(testhost, hostsize < 0 ? (int)strlen(testhost) : hostsize);
	tests++;
	if (strcmp(testhost, expected) != 0) {
		printf("not ok %d - %s\n", tests, test);
		printf("# %s -> %s (expected %s)\n", input, testhost, expected);
	} else
		printf("ok %d - %s\n", tests, test);
	free(testhost);
	return;
}