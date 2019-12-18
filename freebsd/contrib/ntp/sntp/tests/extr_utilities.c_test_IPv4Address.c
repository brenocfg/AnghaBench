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
struct addrinfo {int dummy; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;

/* Variables and functions */
 struct addrinfo CreateAddrinfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateSockaddr4 (char const*) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_STRING (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addrinfo_to_str (struct addrinfo*) ; 
 int /*<<< orphan*/  ss_to_str (int /*<<< orphan*/ *) ; 

void
test_IPv4Address(void) {
	const char* ADDR = "192.0.2.10";

	sockaddr_u input = CreateSockaddr4(ADDR);
	struct addrinfo inputA = CreateAddrinfo(&input);

	TEST_ASSERT_EQUAL_STRING(ADDR, ss_to_str(&input));
	TEST_ASSERT_EQUAL_STRING(ADDR, addrinfo_to_str(&inputA));
}