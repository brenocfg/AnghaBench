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
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_tc_fail (char*) ; 

__attribute__((used)) static void
handler(int sig, siginfo_t *info, void *ctx)
{
	atf_tc_fail("Signal handler was called; "
		"main thread deadlocked in pthread_once()");
}