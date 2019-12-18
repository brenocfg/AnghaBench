#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* s_addr; } ;
struct TYPE_3__ {void* s_addr; } ;
struct ip_mreq {TYPE_2__ imr_interface; TYPE_1__ imr_multiaddr; } ;

/* Variables and functions */
 char* TEST_MADDR ; 
 int /*<<< orphan*/  WARN_SUCCESS ; 
 void* inet_addr (char*) ; 
 int /*<<< orphan*/  test_add_multi (int,char*,struct ip_mreq,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_drop_multi (int,char*,struct ip_mreq,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_addr(int raw_sock, int tcp_sock, int udp_sock)
{
	struct ip_mreq imr;

	/* Arbitrary. */
	imr.imr_multiaddr.s_addr = inet_addr(TEST_MADDR);

	/* Localhost should be OK. */
	imr.imr_interface.s_addr = inet_addr("127.0.0.1");

	test_add_multi(raw_sock, "raw_sock", imr, 0);
	test_drop_multi(raw_sock, "raw_sock", imr, 0);

	test_add_multi(tcp_sock, "raw_sock", imr, WARN_SUCCESS);
	test_drop_multi(tcp_sock, "raw_sock", imr, WARN_SUCCESS);

	test_add_multi(udp_sock, "raw_sock", imr, 0);
	test_drop_multi(udp_sock, "raw_sock", imr, 0);
}