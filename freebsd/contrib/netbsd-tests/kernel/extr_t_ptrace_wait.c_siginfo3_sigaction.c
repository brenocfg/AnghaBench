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
struct TYPE_3__ {int si_signo; int si_code; } ;
typedef  TYPE_1__ siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  FORKEE_ASSERT_EQ (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  TRAP_BRKPT ; 
 int /*<<< orphan*/  siginfo3_caught ; 

__attribute__((used)) static void
siginfo3_sigaction(int sig, siginfo_t *info, void *ctx)
{
	FORKEE_ASSERT_EQ(sig, SIGTRAP);

	FORKEE_ASSERT_EQ(info->si_signo, SIGTRAP);
	FORKEE_ASSERT_EQ(info->si_code, TRAP_BRKPT);

	++siginfo3_caught;
}