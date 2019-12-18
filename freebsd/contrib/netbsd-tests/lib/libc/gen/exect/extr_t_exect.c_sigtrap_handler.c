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
struct TYPE_3__ {int si_code; } ;
typedef  TYPE_1__ siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  TRAP_TRACE ; 
 int /*<<< orphan*/  caught ; 

__attribute__((used)) static void
sigtrap_handler(int sig, siginfo_t *info, void *ctx)
{
	ATF_REQUIRE_EQ(sig, SIGTRAP);
	ATF_REQUIRE_EQ(info->si_code, TRAP_TRACE);

	++caught;
}