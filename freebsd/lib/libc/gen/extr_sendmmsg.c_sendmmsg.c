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
struct mmsghdr {int msg_len; int /*<<< orphan*/  msg_hdr; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int __sys_sendmsg (int,int /*<<< orphan*/ *,int) ; 

ssize_t
sendmmsg(int s, struct mmsghdr *__restrict msgvec, size_t vlen, int flags)
{
	size_t i, sent;
	ssize_t ret;

	sent = 0;
	for (i = 0; i < vlen; i++, sent++) {
		ret = __sys_sendmsg(s, &msgvec[i].msg_hdr, flags);
		if (ret == -1) {
			if (sent != 0) {
				/*
				 * We have sent messages. Let caller
				 * know about the data sent, socket
				 * error is returned on next
				 * invocation.
				 */
				return (sent);
			}
			return (ret);
		}

		/* Save sent bytes. */
		msgvec[i].msg_len = ret;
	}

	return (sent);
}