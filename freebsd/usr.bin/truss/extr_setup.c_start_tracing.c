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
struct trussinfo {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PT_ATTACH ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  new_proc (struct trussinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int) ; 
 scalar_t__ waitpid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
start_tracing(struct trussinfo *info, pid_t pid)
{
	int ret, retry;

	retry = 10;
	do {
		ret = ptrace(PT_ATTACH, pid, NULL, 0);
		usleep(200);
	} while (ret && retry-- > 0);
	if (ret)
		err(1, "can not attach to target process");

	if (waitpid(pid, NULL, 0) < 0)
		err(1, "Unexpect stop in waitpid");

	new_proc(info, pid, 0);
}