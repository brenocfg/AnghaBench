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
 int /*<<< orphan*/  SHUT_WR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  got_signal () ; 
 scalar_t__ shutdown (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_setup (char const*) ; 
 int /*<<< orphan*/  test_send (char const*,int) ; 

__attribute__((used)) static void
test_send_wantsignal(const char *testname, int sock1, int sock2)
{

	if (shutdown(sock2, SHUT_WR) < 0)
		err(-1, "%s: shutdown", testname);
	signal_setup(testname);
	test_send(testname, sock2);
	if (!got_signal())
		errx(-1, "%s: send: didn't receive SIGPIPE", testname);
	close(sock1);
	close(sock2);
}