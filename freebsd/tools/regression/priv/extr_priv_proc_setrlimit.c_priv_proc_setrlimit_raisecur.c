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
struct test {int dummy; } ;
struct rlimit {scalar_t__ rlim_max; scalar_t__ rlim_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  RLIMIT_DATA ; 
 int /*<<< orphan*/  expect (char*,int,int,int /*<<< orphan*/ ) ; 
 struct rlimit rl_lowered ; 
 int setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

void
priv_proc_setrlimit_raisecur(int asroot, int injail, struct test *test)
{
	struct rlimit rl;
	int error;

	rl = rl_lowered;
	rl.rlim_cur = rl.rlim_max + 10;
	error = setrlimit(RLIMIT_DATA, &rl);
	if (asroot && injail)
		expect("priv_proc_setrlimit_raisecur(asroot, injail)", error,
		    0, 0);
	if (asroot && !injail)
		expect("priv_proc_setrlimit_raisecur(asroot, !injail)",
		    error, 0, 0);
	if (!asroot && injail)
		expect("priv_proc_setrlimit_raisecur(!asroot, injail)",
		    error, -1, EPERM);
	if (!asroot && !injail)
		expect("priv_proc_setrlimit_raisecur(!asroot, !injail)",
		    error, -1, EPERM);
}