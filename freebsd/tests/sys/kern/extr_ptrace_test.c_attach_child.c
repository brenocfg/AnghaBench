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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  PT_ATTACH ; 
 scalar_t__ SIGSTOP ; 
 int WIFSTOPPED (int) ; 
 scalar_t__ WSTOPSIG (int) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
attach_child(pid_t pid)
{
	pid_t wpid;
	int status;

	ATF_REQUIRE(ptrace(PT_ATTACH, pid, NULL, 0) == 0);

	wpid = waitpid(pid, &status, 0);
	ATF_REQUIRE(wpid == pid);
	ATF_REQUIRE(WIFSTOPPED(status));
	ATF_REQUIRE(WSTOPSIG(status) == SIGSTOP);
}