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
 int /*<<< orphan*/  DISC_IFNAME ; 
 int /*<<< orphan*/  DISC_IFUNIT ; 
 int /*<<< orphan*/  DISC_IP ; 
 int /*<<< orphan*/  DISC_MASK ; 
 int /*<<< orphan*/  disc_done () ; 
 scalar_t__ disc_setup () ; 
 scalar_t__ ifconfig_inet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multicast_close (int) ; 
 scalar_t__ multicast_open (int*,int,char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static int
test_sock_type(int type, const char *type_string)
{
	int sock;

	if (disc_setup() < 0)
		return (-1);

	if (ifconfig_inet(DISC_IFNAME, DISC_IFUNIT, DISC_IP, DISC_MASK) < 0) {
		disc_done();
		return (-1);
	}

	if (multicast_open(&sock, type, type_string) < 0) {
		disc_done();
		return (-1);
	}

	/*
	 * Tear down the interface first, then close the multicast socket and
	 * see if we make it to the end of the function.
	 */
	disc_done();
	multicast_close(sock);

	printf("test_sock_type(%s) passed\n", type_string);

	return (0);
}