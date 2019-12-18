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
 size_t OPENSSL_ia32_rdrand_bytes (unsigned char*,size_t) ; 

__attribute__((used)) static int get_random_bytes(unsigned char *buf, int num)
{
    if (num < 0) {
        return 0;
    }

    return (size_t)num == OPENSSL_ia32_rdrand_bytes(buf, (size_t)num);
}