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
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  close2 (int,int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  save_sysctls (int*,int*) ; 
 int /*<<< orphan*/  sendfd (int,int) ; 
 char const* test ; 
 int /*<<< orphan*/  test_sysctls (int,int) ; 

__attribute__((used)) static void
fivesome_drop_work(const char *testname, int close_spare_after_send,
    int close_sva_after_send)
{
	int inflight, openfiles;
	int spare, sva[2], svb[2];

	printf("%s\n", testname);
	test = testname;
	save_sysctls(&inflight, &openfiles);
	alloc5fds(&spare, sva, svb);

	/*
	 * Send spare over sva.
	 */
	sendfd(sva[0], spare);
	if (close_spare_after_send)
		close(spare);

	/*
	 * Send sva over svb.
	 */
	sendfd(svb[0], sva[0]);
	sendfd(svb[0], sva[1]);
	if (close_sva_after_send)
		close2(sva[0], sva[1]);

	close2(svb[0], svb[1]);

	if (!close_sva_after_send)
		close2(sva[0], sva[1]);
	if (!close_spare_after_send)
		close(spare);

	test_sysctls(inflight, openfiles);
}