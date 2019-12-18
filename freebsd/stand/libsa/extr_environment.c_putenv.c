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
 int /*<<< orphan*/  free (char*) ; 
 int setenv (char*,char*,int) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 

int
putenv(char *string)
{
    char	*value, *copy;
    int		result;

    copy = strdup(string);
    if ((value = strchr(copy, '=')) != NULL)
	*(value++) = 0;
    result = setenv(copy, value, 1);
    free(copy);
    return(result);
}