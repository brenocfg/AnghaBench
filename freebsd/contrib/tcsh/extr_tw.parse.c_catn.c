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
typedef  char Char ;

/* Variables and functions */

void
catn(Char *des, const Char *src, int count)
{
    while (*des && --count > 0)
	des++;
    while (--count > 0)
	if ((*des++ = *src++) == 0)
	    return;
    *des = '\0';
}