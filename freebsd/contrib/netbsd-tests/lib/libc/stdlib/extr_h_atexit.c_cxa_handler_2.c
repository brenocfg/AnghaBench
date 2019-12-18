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
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  SUCCESS () ; 
 int /*<<< orphan*/  arg_3 ; 
 int exiting_state ; 

__attribute__((used)) static void
cxa_handler_2(void *arg)
{
	static int cxa_handler_2_called;

	ASSERT(arg == (void *)&arg_3);
	ASSERT(cxa_handler_2_called == 0);
	ASSERT(exiting_state == 2);

	exiting_state--;
	cxa_handler_2_called = 1;
	SUCCESS();
}