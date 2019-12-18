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
 int /*<<< orphan*/  arg_1 ; 
 int exiting_state ; 

__attribute__((used)) static void
cxa_handler_4(void *arg)
{
	static int cxa_handler_4_called;

	ASSERT(arg == (void *)&arg_1);
	ASSERT(cxa_handler_4_called == 0);
	ASSERT(exiting_state == 4);

	exiting_state--;
	cxa_handler_4_called = 1;
	SUCCESS();
}