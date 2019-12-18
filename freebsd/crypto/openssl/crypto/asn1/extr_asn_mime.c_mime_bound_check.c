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
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

__attribute__((used)) static int mime_bound_check(char *line, int linelen, const char *bound, int blen)
{
    if (linelen == -1)
        linelen = strlen(line);
    if (blen == -1)
        blen = strlen(bound);
    /* Quickly eliminate if line length too short */
    if (blen + 2 > linelen)
        return 0;
    /* Check for part boundary */
    if ((strncmp(line, "--", 2) == 0)
        && strncmp(line + 2, bound, blen) == 0) {
        if (strncmp(line + blen + 2, "--", 2) == 0)
            return 2;
        else
            return 1;
    }
    return 0;
}