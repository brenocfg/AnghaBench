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
struct test_ctx {int /*<<< orphan*/  tc_fl; int /*<<< orphan*/  tc_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETLKW ; 
 uintptr_t fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_exit (void*) ; 

__attribute__((used)) static void *
test16_func(void *tc_in)
{
	uintptr_t error;
	struct test_ctx *tc = tc_in;

	error = fcntl(tc->tc_fd, F_SETLKW, &tc->tc_fl);

	pthread_exit((void *)error);
}