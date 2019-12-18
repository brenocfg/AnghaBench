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
 char* malloc (size_t) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

char *
unargv(int argc, char *argv[])
{
    size_t	hlong;
    int		i;
    char	*cp;

    for (i = 0, hlong = 0; i < argc; i++)
	hlong += strlen(argv[i]) + 2;

    if(hlong == 0)
	return(NULL);

    cp = malloc(hlong);
    cp[0] = 0;
    for (i = 0; i < argc; i++) {
	strcat(cp, argv[i]);
	if (i < (argc - 1))
	  strcat(cp, " ");
    }
	  
    return(cp);
}