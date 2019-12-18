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
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 char* envName ; 
 char* envValAny ; 
 char* envValLarge ; 
 char* envValSmall ; 
 int /*<<< orphan*/ * environ ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ setenv (char*,char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int unsetenv (char*) ; 

int
main(int argc, char **argv)
{
	const char *env1 = NULL;
	const char *env2 = NULL;
	const char *env3 = NULL;
	const char *env4 = NULL;
	const char *env5 = NULL;
	int testNdx;

	/* Clean slate. */
	environ = NULL;
	testNdx = 0;

	/* Initial value of variable. */
	if (getenv(envName) != NULL)
		printf("not ");
	printf("ok %d - getenv(\"%s\")\n", ++testNdx, envName);

	/* Set value of variable to smaller value and get value. */
	if ((setenv(envName, envValSmall, 1) != 0) ||
	    ((env1 = getenv(envName)) == NULL) ||
	    (strcmp(env1, envValSmall) != 0))
		printf("not ");
	printf("ok %d - setenv(\"%s\", \"%s\", 1)\n", ++testNdx, envName,
	    envValSmall);

	/* Unset variable. */
	if ((unsetenv(envName) == -1) || ((env2 = getenv(envName)) != NULL))
		printf("not ");
	printf("ok %d - unsetenv(\"%s\")\n", ++testNdx, envName);

	/* Set variable to bigger value and get value. */
	if ((setenv(envName, envValLarge, 1) != 0) ||
	    ((env3 = getenv(envName)) == NULL) ||
	    (strcmp(env3, envValLarge) != 0))
		printf("not ");
	printf("ok %d - setenv(\"%s\", \"%s\", 1)\n", ++testNdx, envName,
	    envValLarge);

	/* Set variable to smaller value and get value. */
	if ((setenv(envName, envValSmall, 1) != 0) ||
	    ((env4 = getenv(envName)) == NULL) ||
	    (strcmp(env4, envValSmall) != 0))
		printf("not ");
	printf("ok %d - setenv(\"%s\", \"%s\", 1)\n", ++testNdx, envName,
	    envValSmall);

	/* Set variable to any value without overwrite and get value. */
	if ((setenv(envName, envValAny, 0) != 0) ||
	    ((env5 = getenv(envName)) == NULL) ||
	    (strcmp(env5, envValAny) == 0))
		printf("not ");
	printf("ok %d - setenv(\"%s\", \"%s\", 0)\n", ++testNdx, envName,
	    envValAny);

	/*
	 * Verify FreeBSD-ism about allowing a program to keep old pointers without
	 * risk of segfaulting.
	 */
	if ((strcmp(env1, envValSmall) != 0) ||
	    (strcmp(env3, envValSmall) != 0) ||
	    (strcmp(env4, envValSmall) != 0))
		printf("not ");
	printf("ok %d - old variables point to valid memory\n", ++testNdx);

	exit(EXIT_SUCCESS);
}