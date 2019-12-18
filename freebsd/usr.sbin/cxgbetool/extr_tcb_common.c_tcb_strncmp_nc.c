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
 char EOS ; 
 int tolower (int /*<<< orphan*/ ) ; 

int
tcb_strncmp_nc(char *cs, char *ct, int n)
{
    /*case insensitive version of the standard strncmp() function */
    int i = 0;
    int ret;


    ret = 0;
    for (i = 0; i < n && 0 == ret && !(EOS == *cs && EOS == *ct); ++i) {
        /* this is weird, but it matched GCC linux when strings don't
        * have any upper case characters.
        */
        ret = tolower(*cs++) - tolower(*ct++);
    }
    return ret;
}