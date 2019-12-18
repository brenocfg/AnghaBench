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

/* Variables and functions */
 int /*<<< orphan*/  close2 (int,int) ; 
 int /*<<< orphan*/  my_socketpair (int*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  save_sysctls (int*,int*) ; 
 int /*<<< orphan*/  sendfd (int,int) ; 
 char const* test ; 
 int /*<<< orphan*/  test_sysctls (int,int) ; 

__attribute__((used)) static void
twosome_drop_work(const char *testname, int sendvia, int tosend, int closefirst)
{
	int inflight, openfiles;
	int sv[2];

	printf("%s\n", testname);
	test = testname;
	save_sysctls(&inflight, &openfiles);
	my_socketpair(sv);
	sendfd(sv[sendvia], sv[tosend]);
	if (closefirst == 0)
		close2(sv[0], sv[1]);
	else
		close2(sv[1], sv[0]);
	test_sysctls(inflight, openfiles);
}