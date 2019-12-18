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
 int /*<<< orphan*/  closelog () ; 
 int /*<<< orphan*/  free_sensors () ; 
 int /*<<< orphan*/  lm75_index ; 
 int /*<<< orphan*/  or_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lm75_fini(void)
{

	or_unregister(lm75_index);
	free_sensors();
	closelog();

	return (0);
}