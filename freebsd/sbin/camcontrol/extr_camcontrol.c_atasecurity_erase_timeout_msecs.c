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
typedef  int u_int32_t ;
typedef  int u_int16_t ;

/* Variables and functions */

__attribute__((used)) static u_int32_t
atasecurity_erase_timeout_msecs(u_int16_t timeout)
{

	if (timeout == 0)
		return 2 * 3600 * 1000; /* default: two hours */
	else if (timeout > 255)
		return (508 + 60) * 60 * 1000; /* spec says > 508 minutes */

	return ((2 * timeout) + 5) * 60 * 1000; /* add a 5min margin */
}