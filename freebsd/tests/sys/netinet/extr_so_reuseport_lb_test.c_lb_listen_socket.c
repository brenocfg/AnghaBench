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
typedef  int /*<<< orphan*/  one ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int /*<<< orphan*/ ) ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEPORT_LB ; 
 int /*<<< orphan*/  errno ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int) ; 
 int socket (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lb_listen_socket(int domain, int flags)
{
	size_t one;
	int error, sd;

	sd = socket(domain, SOCK_STREAM | flags, 0);
	ATF_REQUIRE_MSG(sd >= 0, "socket() failed: %s", strerror(errno));

	one = 1;
	error = setsockopt(sd, SOL_SOCKET, SO_REUSEPORT_LB, &one, sizeof(one));
	ATF_REQUIRE_MSG(error == 0, "setsockopt(SO_REUSEPORT_LB) failed: %s",
	    strerror(errno));

	return (sd);
}