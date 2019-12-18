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
 int /*<<< orphan*/  free (char**) ; 
 scalar_t__ malloc (int) ; 
 char* strk (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static char **
construct_argv(char *command)
{
	int argc = 0;
	char **argv = (char **) malloc(((strlen(command) + 1) / 2 + 1)
						* sizeof (char *));

	if ((argv[argc++] = strk(command)) == NULL) {
		free(argv);
		return (NULL);
	}
	while ((argv[argc++] = strk((char *) 0)) != NULL)
		continue;
	return argv;
}