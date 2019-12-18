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
struct tm {int tm_yday; int tm_wday; } ;

/* Variables and functions */

__attribute__((used)) static int
week_number_sun (const struct tm *tm)
{
    return (tm->tm_yday + 7 - (tm->tm_yday % 7 - tm->tm_wday + 7) % 7) / 7;
}