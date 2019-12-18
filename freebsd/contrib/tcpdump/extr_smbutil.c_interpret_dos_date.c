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
typedef  int uint32_t ;
struct tm {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; } ;

/* Variables and functions */

__attribute__((used)) static void
interpret_dos_date(uint32_t date, struct tm *tp)
{
    uint32_t p0, p1, p2, p3;

    p0 = date & 0xFF;
    p1 = ((date & 0xFF00) >> 8) & 0xFF;
    p2 = ((date & 0xFF0000) >> 16) & 0xFF;
    p3 = ((date & 0xFF000000) >> 24) & 0xFF;

    tp->tm_sec = 2 * (p0 & 0x1F);
    tp->tm_min = ((p0 >> 5) & 0xFF) + ((p1 & 0x7) << 3);
    tp->tm_hour = (p1 >> 3) & 0xFF;
    tp->tm_mday = (p2 & 0x1F);
    tp->tm_mon = ((p2 >> 5) & 0xFF) + ((p3 & 0x1) << 3) - 1;
    tp->tm_year = ((p3 >> 1) & 0xFF) + 80;
}