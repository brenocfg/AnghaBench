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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int const,int const) ; 

__attribute__((used)) static const char *
format_interval(const uint32_t n)
{
    static char buf[4][sizeof("0000000.000s")];
    static int i = 0;
    i = (i + 1) % 4;
    snprintf(buf[i], sizeof(buf[i]), "%u.%03us", n / 1000, n % 1000);
    return buf[i];
}