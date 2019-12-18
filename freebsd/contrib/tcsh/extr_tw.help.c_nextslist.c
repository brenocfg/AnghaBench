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
typedef  char Char ;

/* Variables and functions */

__attribute__((used)) static void
nextslist(const Char *sl, Char *np)
{
    if (!*sl)
	*np = '\000';
    else if (*sl == ':') {
	*np++ = '.';
	*np = '\000';
    }
    else {
	while (*sl && *sl != ':')
	    *np++ = *sl++;
	*np = '\000';
    }
}