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
 int strcmp (char const*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int check_end(const char *str, const char *end)
{
    size_t elen, slen;
    const char *tmp;

    elen = strlen(end);
    slen = strlen(str);
    if (elen > slen)
        return 1;
    tmp = str + slen - elen;
    return strcmp(tmp, end);
}