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
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */

__attribute__((used)) static inline register_t
cp0_count_get(void)
{
        register_t count;

        __asm__ __volatile__ ("dmfc0 %0, $9" : "=r" (count));
       return (count);
}