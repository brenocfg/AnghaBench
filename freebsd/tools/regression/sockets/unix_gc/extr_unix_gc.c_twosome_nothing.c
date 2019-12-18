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
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  save_sysctls (int*,int*) ; 
 char* test ; 
 int /*<<< orphan*/  test_sysctls (int,int) ; 

__attribute__((used)) static void
twosome_nothing(void)
{
	int inflight, openfiles;
	int sv[2];

	/*
	 * Create a pair, close in one order.
	 */
	test = "twosome_nothing1";
	printf("%s\n", test);
	save_sysctls(&inflight, &openfiles);
	my_socketpair(sv);
	close2(sv[0], sv[1]);
	test_sysctls(inflight, openfiles);

	/*
	 * Create a pair, close in the other order.
	 */
	test = "twosome_nothing2";
	printf("%s\n", test);
	save_sysctls(&inflight, &openfiles);
	my_socketpair(sv);
	close2(sv[0], sv[1]);
	test_sysctls(inflight, openfiles);
}