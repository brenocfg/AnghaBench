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
 size_t SIZE_MAX ; 
 scalar_t__ memcmp (char const*,char const*,size_t) ; 

size_t h2o_strstr(const char *haysack, size_t haysack_len, const char *needle, size_t needle_len)
{
    /* TODO optimize */
    if (haysack_len >= needle_len) {
        size_t off, max = haysack_len - needle_len + 1;
        if (needle_len == 0)
            return 0;
        for (off = 0; off != max; ++off)
            if (haysack[off] == needle[0] && memcmp(haysack + off + 1, needle + 1, needle_len - 1) == 0)
                return off;
    }
    return SIZE_MAX;
}