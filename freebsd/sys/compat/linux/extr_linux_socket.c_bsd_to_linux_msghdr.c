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
struct msghdr {int /*<<< orphan*/  msg_control; int /*<<< orphan*/  msg_iovlen; int /*<<< orphan*/  msg_iov; int /*<<< orphan*/  msg_namelen; int /*<<< orphan*/  msg_name; } ;
struct l_msghdr {void* msg_control; int /*<<< orphan*/  msg_iovlen; void* msg_iov; int /*<<< orphan*/  msg_namelen; void* msg_name; } ;

/* Variables and functions */
 void* PTROUT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bsd_to_linux_msghdr(const struct msghdr *bhdr, struct l_msghdr *lhdr)
{
	lhdr->msg_name		= PTROUT(bhdr->msg_name);
	lhdr->msg_namelen	= bhdr->msg_namelen;
	lhdr->msg_iov		= PTROUT(bhdr->msg_iov);
	lhdr->msg_iovlen	= bhdr->msg_iovlen;
	lhdr->msg_control	= PTROUT(bhdr->msg_control);

	/*
	 * msg_controllen is skipped since BSD and LINUX control messages
	 * are potentially different sizes (e.g. the cred structure used
	 * by SCM_CREDS is different between the two operating system).
	 *
	 * The caller can set it (if necessary) after converting all the
	 * control messages.
	 */

	/* msg_flags skipped */
	return (0);
}