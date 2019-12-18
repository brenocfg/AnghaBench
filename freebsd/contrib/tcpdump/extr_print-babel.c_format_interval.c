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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int const,int const) ; 

__attribute__((used)) static const char *
format_interval(const uint16_t i)
{
    static char buf[sizeof("000.00s")];

    if (i == 0)
        return "0.0s (bogus)";
    snprintf(buf, sizeof(buf), "%u.%02us", i / 100, i % 100);
    return buf;
}