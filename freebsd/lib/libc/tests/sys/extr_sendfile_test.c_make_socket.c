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
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int socket (int,int,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
make_socket(int domain, int type, int protocol)
{
	int sock;

	sock = socket(domain, type, protocol);
	ATF_REQUIRE_MSG(sock != -1, "socket(%d, %d, 0) failed: %s",
	    domain, type, strerror(errno));

	return (sock);
}