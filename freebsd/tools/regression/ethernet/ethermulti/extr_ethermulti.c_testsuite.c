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
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,int) ; 
 int get_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_ether_multi (int) ; 

__attribute__((used)) static void
testsuite(int priv)
{
	int sock;

	sock = get_socket(SOCK_DGRAM, 0);
	if (sock == -1)
		err(-1, "get_socket(SOCK_DGRAM) for test_ether_multi()", priv);
	test_ether_multi(sock);
	close(sock);
}