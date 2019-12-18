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
 int dlclose_cookie ; 
 int /*<<< orphan*/  poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sleep_fini ; 

__attribute__((used)) static void __attribute__((__destructor__))
fini1(void)
{
	dlclose_cookie = 1;
	if (!sleep_fini)
		return;
	for (;;)
		poll(NULL, 0, -1);
}