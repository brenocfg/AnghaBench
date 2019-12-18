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

int OPENSSL_memcmp(const void *v1, const void *v2, size_t n)
{
    const unsigned char *c1 = v1, *c2 = v2;
    int ret = 0;

    while (n && (ret = *c1 - *c2) == 0)
        n--, c1++, c2++;

    return ret;
}