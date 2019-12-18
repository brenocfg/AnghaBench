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
typedef  int /*<<< orphan*/  u_int32_t ;
struct iovec {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;
struct imsgbuf {int dummy; } ;
struct ibuf {int fd; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int imsg_add (struct ibuf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  imsg_close (struct imsgbuf*,struct ibuf*) ; 
 struct ibuf* imsg_create (struct imsgbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
imsg_composev(struct imsgbuf *ibuf, u_int32_t type, u_int32_t peerid,
    pid_t pid, int fd, const struct iovec *iov, int iovcnt)
{
	struct ibuf	*wbuf;
	int		 i, datalen = 0;

	for (i = 0; i < iovcnt; i++)
		datalen += iov[i].iov_len;

	if ((wbuf = imsg_create(ibuf, type, peerid, pid, datalen)) == NULL)
		return (-1);

	for (i = 0; i < iovcnt; i++)
		if (imsg_add(wbuf, iov[i].iov_base, iov[i].iov_len) == -1)
			return (-1);

	wbuf->fd = fd;

	imsg_close(ibuf, wbuf);

	return (1);
}