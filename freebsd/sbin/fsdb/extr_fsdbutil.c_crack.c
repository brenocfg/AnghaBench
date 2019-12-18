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
 char* strsep (char**,char*) ; 

char **
crack(char *line, int *argc)
{
    static char *argv[8];
    int i;
    char *p, *val;
    for (p = line, i = 0; p != NULL && i < 8; i++) {
	while ((val = strsep(&p, " \t\n")) != NULL && *val == '\0')
	    /**/;
	if (val)
	    argv[i] = val;
	else
	    break;
    }
    *argc = i;
    return argv;
}