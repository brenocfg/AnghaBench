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
struct pkt {int dummy; } ;
typedef  struct pkt sockaddr_u ;

/* Variables and functions */
 int SERVER_AUTH_FAIL ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZERO (struct pkt) ; 
 int /*<<< orphan*/  handle_pkt (int,struct pkt*,struct pkt*,char*) ; 

void
test_HandleServerAuthenticationFailure(void)
{
	struct pkt	rpkt;
	sockaddr_u	host;
	int		rpktl;

	ZERO(rpkt);
	ZERO(host);
	rpktl = SERVER_AUTH_FAIL;
	TEST_ASSERT_EQUAL(1, handle_pkt(rpktl, &rpkt, &host, ""));
}