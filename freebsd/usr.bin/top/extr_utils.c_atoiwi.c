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
 int Infinity ; 
 int Invalid ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 
 scalar_t__ strtol (char const*,int /*<<< orphan*/ *,int) ; 

int
atoiwi(const char *str)
{
    size_t len;

    len = strlen(str);
    if (len != 0)
    {
	if (strncmp(str, "infinity", len) == 0 ||
	    strncmp(str, "all",      len) == 0 ||
	    strncmp(str, "maximum",  len) == 0)
	{
	    return(Infinity);
	}
	else if (str[0] == '-')
	{
	    return(Invalid);
	}
	else
	{
		return((int)strtol(str, NULL, 10));
	}
    }
    return(0);
}