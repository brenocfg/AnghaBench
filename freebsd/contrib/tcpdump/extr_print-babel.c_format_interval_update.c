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

/* Variables and functions */
 char const* format_interval (int const) ; 

__attribute__((used)) static const char *
format_interval_update(const uint16_t i)
{
    return i == 0xFFFF ? "infinity" : format_interval(i);
}