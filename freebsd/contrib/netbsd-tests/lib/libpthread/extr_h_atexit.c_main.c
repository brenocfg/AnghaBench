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
 scalar_t__ __cxa_atexit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *************************) ; 
 int /*<<< orphan*/  __cxa_finalize (int /*<<< orphan*/ *************************) ; 
 int /*<<< orphan*/  arg_1 ; 
 int /*<<< orphan*/  arg_2 ; 
 int /*<<< orphan*/  arg_3 ; 
 scalar_t__ atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxa_handler_2 ; 
 int /*<<< orphan*/  cxa_handler_3 ; 
 int /*<<< orphan*/  cxa_handler_4 ; 
 int /*<<< orphan*/  cxa_handler_5 ; 
 int /*<<< orphan*/ ************************ dso_handle_1 ; 
 int /*<<< orphan*/ ************************ dso_handle_2 ; 
 int /*<<< orphan*/ ************************ dso_handle_3 ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int exiting_state ; 
 int /*<<< orphan*/  normal_handler_0 ; 
 int /*<<< orphan*/  normal_handler_1 ; 

int
main(int argc, char *argv[])
{

	exiting_state = 5;

#ifdef __FreeBSD__
	ASSERT(0 == atexit(normal_handler_0));
	ASSERT(0 == atexit(normal_handler_1));
	ASSERT(0 == __cxa_atexit(cxa_handler_4, &arg_1, dso_handle_1));
	ASSERT(0 == __cxa_atexit(cxa_handler_5, &arg_1, dso_handle_1));
	ASSERT(0 == __cxa_atexit(cxa_handler_3, &arg_2, dso_handle_2));
	ASSERT(0 == __cxa_atexit(cxa_handler_2, &arg_3, dso_handle_3));

	__cxa_finalize(dso_handle_1);
	__cxa_finalize(dso_handle_2);
#else
	ASSERT(0 == __cxa_atexit(cxa_handler_4, &arg_1, &dso_handle_1));
	ASSERT(0 == __cxa_atexit(cxa_handler_5, &arg_1, &dso_handle_1));
	ASSERT(0 == __cxa_atexit(cxa_handler_3, &arg_2, &dso_handle_2));
	ASSERT(0 == __cxa_atexit(cxa_handler_2, &arg_3, &dso_handle_3));

	__cxa_finalize(&dso_handle_1);
	__cxa_finalize(&dso_handle_2);
#endif
	exit(0);
}