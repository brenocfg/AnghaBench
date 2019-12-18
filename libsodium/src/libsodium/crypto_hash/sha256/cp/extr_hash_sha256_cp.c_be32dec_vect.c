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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOAD32_BE (unsigned char const*) ; 

__attribute__((used)) static void
be32dec_vect(uint32_t *dst, const unsigned char *src, size_t len)
{
    size_t i;

    for (i = 0; i < len / 4; i++) {
        dst[i] = LOAD32_BE(src + i * 4);
    }
}