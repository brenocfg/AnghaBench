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
 int strncmp (char const*,char const*,int) ; 

int name_cmp(const char *name, const char *cmp)
{
    int len, ret;
    char c;
    len = strlen(cmp);
    if ((ret = strncmp(name, cmp, len)))
        return ret;
    c = name[len];
    if (!c || (c == '.'))
        return 0;
    return 1;
}