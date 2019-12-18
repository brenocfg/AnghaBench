#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  s; } ;
struct skt {int /*<<< orphan*/  len; TYPE_1__ sktaddr; } ;

/* Variables and functions */
 scalar_t__ EADDRNOTAVAIL ; 
 scalar_t__ UDP_SOCKET_MAX_SENDTO ; 
 scalar_t__ errno ; 
 int sendto (int,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int try_send_to(int sock_fd, void *buff, size_t buf_size,
		       struct skt *addr_dst)
{
	uint64_t max_count = UDP_SOCKET_MAX_SENDTO;
	int err;

	do {
		err = sendto(sock_fd, buff, buf_size, 0,
			     &addr_dst->sktaddr.s,
			     addr_dst->len);
		if (err > 0)
			err = 0;
	} while (-1 == err && EADDRNOTAVAIL == errno && --max_count);

	return err;
}