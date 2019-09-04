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
typedef  int uint64_t ;

/* Variables and functions */
 int SIZE_MAX ; 

size_t h2o_strtosizefwd(char **s, size_t len)
{
    uint64_t v, c;
    char *p = *s, *p_end = *s + len;

    if (len == 0)
        goto Error;

    int ch = *p++;
    if (!('0' <= ch && ch <= '9'))
        goto Error;
    v = ch - '0';
    c = 1;

    while (1) {
        ch = *p;
        if (!('0' <= ch && ch <= '9'))
            break;
        v *= 10;
        v += ch - '0';
        p++;
        c++;
        if (p == p_end)
            break;
        /* similar as above, do not even try to overflow */
        if (c == 20)
            goto Error;
    }

    if (v >= SIZE_MAX)
        goto Error;
    *s = p;
    return v;

Error:
    return SIZE_MAX;
}