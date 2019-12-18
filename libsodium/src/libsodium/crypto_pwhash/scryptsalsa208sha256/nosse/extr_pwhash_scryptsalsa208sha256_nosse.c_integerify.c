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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  scalar_t__ B ;

/* Variables and functions */

__attribute__((used)) static inline uint64_t
integerify(const void *B, size_t r)
{
    const uint32_t *X = (const uint32_t *) ((uintptr_t)(B) + (2 * r - 1) * 64);

    return (((uint64_t)(X[1]) << 32) + X[0]);
}