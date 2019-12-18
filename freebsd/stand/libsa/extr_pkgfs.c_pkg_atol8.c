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
typedef  int off_t ;
typedef  int int64_t ;

/* Variables and functions */
 int INT64_MAX ; 
 int UINT64_MAX ; 

__attribute__((used)) static off_t
pkg_atol8(const char *p, unsigned char_cnt)
{
        int64_t l, limit, last_digit_limit;
        int digit, sign, base;

        base = 8;
        limit = INT64_MAX / base;
        last_digit_limit = INT64_MAX % base;

        while (*p == ' ' || *p == '\t')
                p++;
        if (*p == '-') {
                sign = -1;
                p++;
        } else
                sign = 1;

        l = 0;
        digit = *p - '0';
        while (digit >= 0 && digit < base  && char_cnt-- > 0) {
                if (l>limit || (l == limit && digit > last_digit_limit)) {
                        l = UINT64_MAX; /* Truncate on overflow. */
                        break;
                }
                l = (l * base) + digit;
                digit = *++p - '0';
        }
        return (sign < 0) ? -l : l;
}