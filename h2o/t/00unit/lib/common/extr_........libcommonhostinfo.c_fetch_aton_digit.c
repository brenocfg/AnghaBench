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

__attribute__((used)) static const char *fetch_aton_digit(const char *p, const char *end, unsigned char *value)
{
    size_t ndigits = 0;
    int v = 0;

    while (p != end && ('0' <= *p && *p <= '9')) {
        v = v * 10 + *p++ - '0';
        ++ndigits;
    }
    if (!(1 <= ndigits && ndigits <= 3))
        return NULL;
    if (v > 255)
        return NULL;
    *value = (unsigned char)v;
    return p;
}