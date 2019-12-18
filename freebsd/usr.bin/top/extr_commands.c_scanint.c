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
 scalar_t__ isdigit (char) ; 
 scalar_t__ isspace (char) ; 

__attribute__((used)) static int
scanint(char *str, int *intp)
{
    int val = 0;
    char ch;

    /* if there is nothing left of the string, flag it as an error */
    /* This fix is dedicated to Greg Earle */
    if (*str == '\0')
    {
	return(-1);
    }

    while ((ch = *str++) != '\0')
    {
	if (isdigit(ch))
	{
	    val = val * 10 + (ch - '0');
	}
	else if (isspace(ch))
	{
	    break;
	}
	else
	{
	    return(-1);
	}
    }
    *intp = val;
    return(0);
}