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
 scalar_t__ ISSPACE (char) ; 

__attribute__((used)) static char *
gettoken(char **pptr, char *token)
{
    char *ptr = *pptr;
    char *tok = token;

    for (; *ptr && ISSPACE(*ptr); ptr++)
	continue;

    for (; *ptr && *ptr != ':'; *tok++ = *ptr++)
	continue;

    if (*ptr == ':')
	ptr++;
    else
	tok--;

    for (tok--; tok >= token && *tok && ISSPACE(*tok); tok--)
	continue;

    *++tok = '\0';

    *pptr = ptr;
    return token;
}