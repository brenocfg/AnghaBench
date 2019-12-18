#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* cmd; char* text; char* desc; } ;

/* Variables and functions */
 TYPE_1__* commands ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int
cmd_help(int argc, char *argv[]) 
{
    int		i;
    
    if (argc > 1)
	for (i = 0; commands[i].cmd != NULL; i++)
	    if (!strcmp(argv[1], commands[i].cmd)) {
		fprintf(stderr, "%s\n", commands[i].text);
		fflush(stderr);
		return(0);
	    }

    if (argv != NULL)
	fprintf(stderr, "Unknown command '%s'.\n", argv[1]);    
    fprintf(stderr, "Valid commands are:\n");
    for (i = 0; commands[i].cmd != NULL; i++)
	fprintf(stderr, "  %-20s %s\n", commands[i].cmd, commands[i].desc);
    fflush(stderr);
    return(0);
}