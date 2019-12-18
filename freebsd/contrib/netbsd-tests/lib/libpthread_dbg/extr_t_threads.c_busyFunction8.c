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
 scalar_t__ exiting8 ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void *
busyFunction8(void *arg)
{

	while (exiting8 == 0)
		usleep(50000);

	return NULL;
}