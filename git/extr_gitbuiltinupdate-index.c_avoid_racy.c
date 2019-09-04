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
 int /*<<< orphan*/  sleep (int) ; 

__attribute__((used)) static void avoid_racy(void)
{
	/*
	 * not use if we could usleep(10) if USE_NSEC is defined. The
	 * field nsec could be there, but the OS could choose to
	 * ignore it?
	 */
	sleep(1);
}