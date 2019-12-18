#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct test {int dummy; } ;
struct rlimit {int /*<<< orphan*/  rlim_max; } ;
struct TYPE_2__ {int /*<<< orphan*/  rlim_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  RLIMIT_DATA ; 
 int /*<<< orphan*/  expect (char*,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ rl_base ; 
 struct rlimit rl_lowered ; 
 int setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

void
priv_proc_setrlimit_raisemax(int asroot, int injail, struct test *test)
{
	struct rlimit rl;
	int error;

	rl = rl_lowered;
	rl.rlim_max = rl_base.rlim_max;
	error = setrlimit(RLIMIT_DATA, &rl);
	if (asroot && injail)
		expect("priv_proc_setrlimit_raisemax(asroot, injail)", error,
		    0, 0);
	if (asroot && !injail)
		expect("priv_proc_setrlimit_raisemax(asroot, !injail)",
		    error, 0, 0);
	if (!asroot && injail)
		expect("priv_proc_setrlimit_raisemax(!asroot, injail)",
		    error, -1, EPERM);
	if (!asroot && !injail)
		expect("priv_proc_setrlimit_raisemax(!asroot, !injail)",
		    error, -1, EPERM);
}