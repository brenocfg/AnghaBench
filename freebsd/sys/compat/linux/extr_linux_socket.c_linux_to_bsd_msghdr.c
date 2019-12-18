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
struct msghdr {int /*<<< orphan*/  msg_flags; void* msg_control; int /*<<< orphan*/  msg_iovlen; void* msg_iov; int /*<<< orphan*/  msg_namelen; void* msg_name; } ;
struct l_msghdr {scalar_t__ msg_controllen; int /*<<< orphan*/  msg_flags; int /*<<< orphan*/  msg_control; int /*<<< orphan*/  msg_iovlen; int /*<<< orphan*/  msg_iov; int /*<<< orphan*/  msg_namelen; int /*<<< orphan*/  msg_name; } ;

/* Variables and functions */
 int ENOBUFS ; 
 scalar_t__ INT_MAX ; 
 void* PTRIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_to_bsd_msg_flags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
linux_to_bsd_msghdr(struct msghdr *bhdr, const struct l_msghdr *lhdr)
{
	if (lhdr->msg_controllen > INT_MAX)
		return (ENOBUFS);

	bhdr->msg_name		= PTRIN(lhdr->msg_name);
	bhdr->msg_namelen	= lhdr->msg_namelen;
	bhdr->msg_iov		= PTRIN(lhdr->msg_iov);
	bhdr->msg_iovlen	= lhdr->msg_iovlen;
	bhdr->msg_control	= PTRIN(lhdr->msg_control);

	/*
	 * msg_controllen is skipped since BSD and LINUX control messages
	 * are potentially different sizes (e.g. the cred structure used
	 * by SCM_CREDS is different between the two operating system).
	 *
	 * The caller can set it (if necessary) after converting all the
	 * control messages.
	 */

	bhdr->msg_flags		= linux_to_bsd_msg_flags(lhdr->msg_flags);
	return (0);
}