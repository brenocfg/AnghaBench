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

/* Variables and functions */
 scalar_t__ TS_CLOSED ; 
 scalar_t__ TS_OPEN ; 
 int /*<<< orphan*/  rmtcall (char*,char*) ; 
 scalar_t__ rmtstate ; 

void
rmtclose(void)
{

	if (rmtstate != TS_OPEN)
		return;
	rmtcall("close", "C\n");
	rmtstate = TS_CLOSED;
}