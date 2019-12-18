#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; char* help; } ;
typedef  TYPE_1__ Command ;

/* Variables and functions */
 scalar_t__ Ambiguous (TYPE_1__*) ; 
 char* HELPINDENT ; 
 TYPE_1__* cmdtab ; 
 TYPE_1__* getcmd (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
help(int argc, char **argv)
{
	Command *c;

	if (argc == 1) {
		printf("Commands may be abbreviated.  Commands are:\r\n\r\n");
		for (c = cmdtab; c->name; c++)
			if (c->help) {
				printf("%-*s\t%s\r\n", HELPINDENT, c->name,
								    c->help);
			}
		return 0;
	}
	while (--argc > 0) {
		char *arg;
		arg = *++argv;
		c = getcmd(arg);
		if (Ambiguous(c))
			printf("?Ambiguous help command %s\r\n", arg);
		else if (c == (Command *)0)
			printf("?Invalid help command %s\r\n", arg);
		else
			printf("%s\r\n", c->help);
	}
	return 0;
}