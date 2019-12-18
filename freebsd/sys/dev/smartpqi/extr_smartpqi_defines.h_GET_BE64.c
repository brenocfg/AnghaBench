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
typedef  int uint64_t ;

/* Variables and functions */
 int GET_BE32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline uint64_t GET_BE64(const uint8_t *p)
{
        return (((uint64_t)GET_BE32(p) << 32) |
               GET_BE32(p + 4));
}