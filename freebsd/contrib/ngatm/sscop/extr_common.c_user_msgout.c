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
typedef  void* u_int32_t ;
struct uni_msg {scalar_t__ b_rptr; } ;
struct iovec {int iov_len; scalar_t__ iov_base; } ;
typedef  int ssize_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 
 void* uni_msg_len (struct uni_msg*) ; 
 scalar_t__ useframe ; 
 int /*<<< orphan*/  user_out_fd ; 
 int writev (int /*<<< orphan*/ ,struct iovec*,int) ; 

void
user_msgout(struct uni_msg *m)
{
	struct iovec iov[2];
	u_int32_t flen;
	ssize_t size;

	flen = uni_msg_len(m);

	iov[0].iov_len = useframe ? 4 : 0;
	iov[0].iov_base = (caddr_t)&flen;
	iov[1].iov_len = uni_msg_len(m);
	iov[1].iov_base = m->b_rptr;

	if ((size = writev(user_out_fd, iov, 2)) == -1)
		err(1, "write sscop");
	if ((size_t)size != iov[0].iov_len + iov[1].iov_len)
		errx(1, "short sscop write");

	uni_msg_destroy(m);
}