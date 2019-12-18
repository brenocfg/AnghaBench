#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  si_signo; } ;
typedef  TYPE_1__ siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ_MSG (int /*<<< orphan*/ ,int,char*) ; 
 int alarm_set ; 

__attribute__((used)) static void
alarm_handler(int signo, siginfo_t *si, void *ctx)
{
	ATF_REQUIRE_EQ_MSG(si->si_signo, signo, "Received unexpected signal");
	alarm_set = 1;
}