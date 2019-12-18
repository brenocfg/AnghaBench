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
 scalar_t__ tolower (unsigned char) ; 

int
isprefix(char *s1, char *s2)
{
    char *os1;
    char c1, c2;

    if (*s1 == '\0')
	return(-1);
    os1 = s1;
    c1 = *s1;
    c2 = *s2;
    while (tolower((unsigned char)c1) == tolower((unsigned char)c2)) {
	if (c1 == '\0')
	    break;
	c1 = *++s1;
	c2 = *++s2;
    }
    return(*s1 ? 0 : (*s2 ? (s1 - os1) : (os1 - s1)));
}