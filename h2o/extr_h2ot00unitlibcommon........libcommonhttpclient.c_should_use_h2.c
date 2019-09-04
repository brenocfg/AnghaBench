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
typedef  int int8_t ;

/* Variables and functions */

__attribute__((used)) static int should_use_h2(int8_t ratio, int8_t *counter)
{
    /* weighted fair queueing */
    if (*counter < 0)
        *counter = ratio == 0 ? 0 : 50 / ratio; /* set initial counter value */
    int use_h2 = (((int)ratio * *counter) % 100) + ratio >= 100;
    if (++*counter == 100)
        *counter = 0;
    return use_h2;
}