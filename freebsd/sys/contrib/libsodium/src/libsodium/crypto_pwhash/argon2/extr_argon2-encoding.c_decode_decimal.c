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
 int ULONG_MAX ; 

__attribute__((used)) static const char *
decode_decimal(const char *str, unsigned long *v)
{
    const char    *orig;
    unsigned long  acc;

    acc = 0;
    for (orig = str;; str++) {
        int c;

        c = *str;
        if (c < '0' || c > '9') {
            break;
        }
        c -= '0';
        if (acc > (ULONG_MAX / 10)) {
            return NULL;
        }
        acc *= 10;
        if ((unsigned long) c > (ULONG_MAX - acc)) {
            return NULL;
        }
        acc += (unsigned long) c;
    }
    if (str == orig || (*orig == '0' && str != (orig + 1))) {
        return NULL;
    }
    *v = acc;
    return str;
}