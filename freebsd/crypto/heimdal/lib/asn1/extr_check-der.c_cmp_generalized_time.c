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
typedef  int time_t ;

/* Variables and functions */

__attribute__((used)) static int
cmp_generalized_time (void *a, void *b)
{
    time_t *ta = (time_t *)a;
    time_t *tb = (time_t *)b;

    return *tb - *ta;
}