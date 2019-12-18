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
#define  C_COMMON 130 
#define  C_DIFFERENCE 129 
#define  C_NAND 128 
 char* _nc_progname ; 
 int compare ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ itrace ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
show_comparing(char **names)
{
    if (itrace) {
	switch (compare) {
	case C_DIFFERENCE:
	    (void) fprintf(stderr, "%s: dumping differences\n", _nc_progname);
	    break;

	case C_COMMON:
	    (void) fprintf(stderr, "%s: dumping common capabilities\n", _nc_progname);
	    break;

	case C_NAND:
	    (void) fprintf(stderr, "%s: dumping differences\n", _nc_progname);
	    break;
	}
    }
    if (*names) {
	printf("comparing %s", *names++);
	if (*names) {
	    printf(" to %s", *names++);
	    while (*names) {
		printf(", %s", *names++);
	    }
	}
	printf(".\n");
    }
}