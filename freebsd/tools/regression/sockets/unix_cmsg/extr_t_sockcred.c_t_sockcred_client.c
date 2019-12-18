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
struct msghdr {int dummy; } ;
struct iovec {int dummy; } ;

/* Variables and functions */
 scalar_t__ uc_message_sendn (int,struct msghdr*) ; 
 int /*<<< orphan*/  uc_msghdr_init_client (struct msghdr*,struct iovec*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uc_socket_connect (int) ; 
 scalar_t__ uc_sync_recv () ; 

__attribute__((used)) static int
t_sockcred_client(int type, int fd)
{
	struct msghdr msghdr;
	struct iovec iov[1];
	int rv;

	if (uc_sync_recv() < 0)
		return (-2);

	rv = -2;

	uc_msghdr_init_client(&msghdr, iov, NULL, 0, 0, 0);

	if (uc_socket_connect(fd) < 0)
		goto done;

	if (type == 2)
		if (uc_sync_recv() < 0)
			goto done;

	if (uc_message_sendn(fd, &msghdr) < 0)
		goto done;

	rv = 0;
done:
	return (rv);
}