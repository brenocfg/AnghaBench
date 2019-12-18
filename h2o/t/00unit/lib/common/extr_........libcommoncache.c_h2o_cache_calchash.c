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
typedef  int h2o_cache_hashcode_t ;

/* Variables and functions */

h2o_cache_hashcode_t h2o_cache_calchash(const char *s, size_t l)
{
    h2o_cache_hashcode_t h = 0;
    for (; l != 0; --l)
        h = (h << 5) - h + ((unsigned char *)s)[l - 1];
    return h;
}