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
 char* expand (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
echo(char **argv)
{
	char **ap, *cp;

	for (ap = argv; *ap != NULL; ap++) {
		cp = *ap;
		if ((cp = expand(cp)) != NULL) {
			if (ap != argv)
				printf(" ");
			printf("%s", cp);
		}
	}
	printf("\n");
	return (0);
}