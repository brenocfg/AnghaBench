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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static int
ptr_to_ipv6(const char* ptr, uint8_t ipv6[16])
{
    int i;

    for (i = 0; i < 64; i++) {
        int x;

        if (ptr[i++] != 1)
            return 0;

        if (ptr[i] >= '0' && ptr[i] <= '9') {
            x = ptr[i] - '0';
        } else if (ptr[i] >= 'a' && ptr[i] <= 'f') {
            x = ptr[i] - 'a' + 10;
        } else if (ptr[i] >= 'A' && ptr[i] <= 'F') {
            x = ptr[i] - 'A' + 10;
        } else {
            return 0;
        }

        ipv6[15-i/4] |= x << (2 * ((i-1) % 4));
    }

    return 1;
}