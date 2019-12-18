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
struct cmdtab {char* name; char* args; int min; } ;

/* Variables and functions */
 struct cmdtab* cmdtab ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 char toupper (char const) ; 

__attribute__((used)) static void
help(void)
{
	struct cmdtab *c;
	const char *s;
	char n;
	int i;

	for (c=cmdtab; c->name; ++c) {
		if (! c->args)
			continue;
		printf("\t");
		for (i = c->min, s = c->name; *s; s++, i--) {
			if (i > 0)
				n = toupper(*s);
			else
				n = *s;
			putchar(n);
		}
		if (*c->args)
			printf (" %s", c->args);
		printf ("\n");
	}
	printf ("\n\tThe word \"play\" is not required for the play commands.\n");
	printf ("\tThe plain target address is taken as a synonym for play.\n");
}