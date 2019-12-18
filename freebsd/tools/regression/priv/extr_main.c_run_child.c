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
struct test {int /*<<< orphan*/  (* t_test_func ) (int,int,struct test*) ;int /*<<< orphan*/  t_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GID_OWNER ; 
 int /*<<< orphan*/  UID_OWNER ; 
 int /*<<< orphan*/  enter_jail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_creds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setprogname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int,struct test*) ; 

__attribute__((used)) static void
run_child(struct test *test, int asroot, int injail)
{

	setprogname(test->t_name);
	if (injail)
		enter_jail(test->t_name);
	if (!asroot)
		set_creds(test->t_name, UID_OWNER, GID_OWNER);
	test->t_test_func(asroot, injail, test);
}