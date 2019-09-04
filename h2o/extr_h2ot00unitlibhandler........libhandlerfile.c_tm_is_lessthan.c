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
struct tm {scalar_t__ tm_year; scalar_t__ tm_mon; scalar_t__ tm_mday; scalar_t__ tm_hour; scalar_t__ tm_min; scalar_t__ tm_sec; } ;

/* Variables and functions */

__attribute__((used)) static int tm_is_lessthan(struct tm *x, struct tm *y)
{
#define CMP(f)                                                                                                                     \
    if (x->f < y->f)                                                                                                               \
        return 1;                                                                                                                  \
    else if (x->f > y->f)                                                                                                          \
        return 0;
    CMP(tm_year);
    CMP(tm_mon);
    CMP(tm_mday);
    CMP(tm_hour);
    CMP(tm_min);
    CMP(tm_sec);
    return 0;
#undef CMP
}