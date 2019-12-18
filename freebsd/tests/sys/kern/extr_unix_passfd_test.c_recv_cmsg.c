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
struct msghdr {char* msg_control; size_t msg_controllen; int msg_iovlen; int msg_flags; struct iovec* msg_iov; } ;
struct iovec {char* iov_base; int iov_len; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  msghdr ;
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int,...) ; 
 int /*<<< orphan*/  bzero (struct msghdr*,int) ; 
 int /*<<< orphan*/  errno ; 
 int recvmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
recv_cmsg(int sockfd, char *cmsg, size_t cmsgsz, int flags)
{
	struct iovec iov;
	struct msghdr msghdr;
	ssize_t len;
	char ch;

	ch = 0;
	bzero(&msghdr, sizeof(msghdr));

	iov.iov_base = &ch;
	iov.iov_len = sizeof(ch);
	msghdr.msg_control = cmsg;
	msghdr.msg_controllen = cmsgsz;
	msghdr.msg_iov = &iov;
	msghdr.msg_iovlen = 1;

	len = recvmsg(sockfd, &msghdr, 0);
	ATF_REQUIRE_MSG(len != -1,
	    "recvmsg failed: %s", strerror(errno));
	ATF_REQUIRE_MSG(len == sizeof(ch),
	    "recvmsg: %zd bytes received; expected %zu", len, sizeof(ch));
	ATF_REQUIRE_MSG((msghdr.msg_flags & flags) == flags,
	    "recvmsg: got flags %#x; expected %#x", msghdr.msg_flags, flags);
}