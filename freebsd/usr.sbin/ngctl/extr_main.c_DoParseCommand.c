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
 int DoCommand (int,char**) ; 
 int MAX_ARGS ; 
 int /*<<< orphan*/  WHITESPACE ; 
 char* strtok (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
DoParseCommand(const char *line)
{
	char *av[MAX_ARGS];
	int ac;

	/* Parse line */
	for (ac = 0, av[0] = strtok((char *)line, WHITESPACE);
	    ac < MAX_ARGS - 1 && av[ac];
	    av[++ac] = strtok(NULL, WHITESPACE));

	/* Do command */
	return (DoCommand(ac, av));
}