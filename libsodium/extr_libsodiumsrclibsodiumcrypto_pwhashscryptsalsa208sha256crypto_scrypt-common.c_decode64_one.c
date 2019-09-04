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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 char const* itoa64 ; 
 char* strchr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
decode64_one(uint32_t *dst, uint8_t src)
{
    const char *ptr = strchr(itoa64, src);

    if (ptr) {
        *dst = (uint32_t)(ptr - itoa64);
        return 0;
    }
    *dst = 0;

    return -1;
}