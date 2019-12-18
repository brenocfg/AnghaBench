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
 int /*<<< orphan*/  EADDRINUSE ; 
 int /*<<< orphan*/  ipdivert_bind (char const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipdivert_close (char const*,int) ; 
 int ipdivert_create (char const*) ; 
 int /*<<< orphan*/  ok (char const*) ; 

int
main(int argc, char *argv[])
{
	const char *test;
	int s1, s2;

	/*
	 * First test: create and close an IP divert socket.
	 */
	test = "create_close";
	s1 = ipdivert_create(test);
	ipdivert_close(test, s1);
	ok(test);

	/*
	 * Second test: create, bind, and close an IP divert socket.
	 */
	test = "create_bind_close";
	s1 = ipdivert_create(test);
	ipdivert_bind(test, s1, 1000, 0);
	ipdivert_close(test, s1);
	ok(test);

	/*
	 * Third test: create two sockets, bind to different ports, and close.
	 * This should succeed due to non-conflict on the port numbers.
	 */
	test = "create2_bind2_close2";
	s1 = ipdivert_create(test);
	s2 = ipdivert_create(test);
	ipdivert_bind(test, s1, 1000, 0);
	ipdivert_bind(test, s2, 1001, 0);
	ipdivert_close(test, s1);
	ipdivert_close(test, s2);
	ok(test);

	/*
	 * Fourth test: create two sockets, bind to the *same* port, and
	 * close.  This should fail due to conflicting port numbers.
	 */
	test = "create2_bind2_conflict_close2";
	s1 = ipdivert_create(test);
	s2 = ipdivert_create(test);
	ipdivert_bind(test, s1, 1000, 0);
	ipdivert_bind(test, s2, 1000, EADDRINUSE);
	ipdivert_close(test, s1);
	ipdivert_close(test, s2);
	ok(test);

	return (0);
}