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

__attribute__((used)) static int sysv_chksm(const unsigned char *data, int size)
{
    int r;
    int checksum;
    unsigned int s = 0; /* The sum of all the input bytes, modulo (UINT_MAX + 1).  */


    for (int i = 0; i < size; i++) {
        s += data[i];
    }

    r = (s & 0xffff) + ((s & 0xffffffff) >> 16);
    checksum = (r & 0xffff) + (r >> 16);

    return checksum;
}