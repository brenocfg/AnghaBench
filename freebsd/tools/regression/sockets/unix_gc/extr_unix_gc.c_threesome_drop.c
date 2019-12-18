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
 int /*<<< orphan*/  alloc3fds (int*,int*) ; 
 int /*<<< orphan*/  close3 (int,int,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  save_sysctls (int*,int*) ; 
 int /*<<< orphan*/  sendfd (int,int) ; 
 char* test ; 
 int /*<<< orphan*/  test_sysctls (int,int) ; 

__attribute__((used)) static void
threesome_drop(void)
{
	int inflight, openfiles;
	int s, sv[2];

	/*
	 * threesome_drop1: close sent send receive
	 */
	test = "threesome_drop1";
	printf("%s\n", test);
	save_sysctls(&inflight, &openfiles);
	alloc3fds(&s, sv);
	sendfd(sv[0], s);
	close3(s, sv[0], sv[1]);
	test_sysctls(inflight, openfiles);

	/*
	 * threesome_drop2: close sent receive send
	 */
	test = "threesome_drop2";
	printf("%s\n", test);
	save_sysctls(&inflight, &openfiles);
	alloc3fds(&s, sv);
	sendfd(sv[0], s);
	close3(s, sv[1], sv[0]);
	test_sysctls(inflight, openfiles);

	/*
	 * threesome_drop3: close receive sent send
	 */
	test = "threesome_drop3";
	printf("%s\n", test);
	save_sysctls(&inflight, &openfiles);
	alloc3fds(&s, sv);
	sendfd(sv[0], s);
	close3(sv[1], s, sv[0]);
	test_sysctls(inflight, openfiles);

	/*
	 * threesome_drop4: close receive send sent
	 */
	test = "threesome_drop4";
	printf("%s\n", test);
	save_sysctls(&inflight, &openfiles);
	alloc3fds(&s, sv);
	sendfd(sv[0], s);
	close3(sv[1], sv[0], s);
	test_sysctls(inflight, openfiles);

	/*
	 * threesome_drop5: close send receive sent
	 */
	test = "threesome_drop5";
	printf("%s\n", test);
	save_sysctls(&inflight, &openfiles);
	alloc3fds(&s, sv);
	sendfd(sv[0], s);
	close3(sv[0], sv[1], s);
	test_sysctls(inflight, openfiles);

	/*
	 * threesome_drop6: close send sent receive
	 */
	test = "threesome_drop6";
	printf("%s\n", test);
	save_sysctls(&inflight, &openfiles);
	alloc3fds(&s, sv);
	close3(sv[0], s, sv[1]);
	test_sysctls(inflight, openfiles);
}