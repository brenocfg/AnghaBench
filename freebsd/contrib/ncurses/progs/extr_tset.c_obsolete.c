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
 char* strdup (char*) ; 

__attribute__((used)) static void
obsolete(char **argv)
{
    for (; *argv; ++argv) {
	char *parm = argv[0];

	if (parm[0] == '-' && parm[1] == '\0') {
	    argv[0] = strdup("-q");
	    continue;
	}

	if ((parm[0] != '-')
	    || (argv[1] && argv[1][0] != '-')
	    || (parm[1] != 'e' && parm[1] != 'i' && parm[1] != 'k')
	    || (parm[2] != '\0'))
	    continue;
	switch (argv[0][1]) {
	case 'e':
	    argv[0] = strdup("-e^H");
	    break;
	case 'i':
	    argv[0] = strdup("-i^C");
	    break;
	case 'k':
	    argv[0] = strdup("-k^U");
	    break;
	}
    }
}