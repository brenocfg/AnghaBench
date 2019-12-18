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
 int /*<<< orphan*/  alloc5fds (int*,int*,int*) ; 
 int /*<<< orphan*/  close5 (int,int,int,int,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  save_sysctls (int*,int*) ; 
 int /*<<< orphan*/  sendfd (int,int) ; 
 char* test ; 
 int /*<<< orphan*/  test_sysctls (int,int) ; 

__attribute__((used)) static void
complex_cycles(void)
{
	int inflight, openfiles;
	int spare, sva[2], svb[2];

	test = "complex_cycles";
	printf("%s\n", test);
	save_sysctls(&inflight, &openfiles);
	alloc5fds(&spare, sva, svb);
	sendfd(sva[0], svb[0]);
	sendfd(sva[0], svb[1]);
	sendfd(svb[0], sva[0]);
	sendfd(svb[0], sva[1]);
	sendfd(svb[0], spare);
	sendfd(sva[0], spare);
	close5(spare, sva[0], sva[1], svb[0], svb[1]);
	test_sysctls(inflight, openfiles);
}