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
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 size_t sendfd_payload (int,int,char*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sendfd(int sockfd, int send_fd)
{
	size_t len;
	char ch;

	ch = 0;
	len = sendfd_payload(sockfd, send_fd, &ch, sizeof(ch));
	ATF_REQUIRE_MSG(len == sizeof(ch),
	    "sendmsg: %zu bytes sent; expected %zu; %s", len, sizeof(ch),
	    strerror(errno));
}