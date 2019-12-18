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
struct socket_info {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ ENOBUFS ; 
 int /*<<< orphan*/  SWRAP_RECV ; 
 int /*<<< orphan*/  SWRAP_RECV_RST ; 
 scalar_t__ errno ; 
 struct socket_info* find_socket_info (int) ; 
 int real_recv (int,void*,size_t,int) ; 
 int /*<<< orphan*/  swrap_dump_packet (struct socket_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int) ; 

ssize_t swrap_recv(int s, void *buf, size_t len, int flags)
{
	int ret;
	struct socket_info *si = find_socket_info(s);

	if (!si) {
		return real_recv(s, buf, len, flags);
	}

	ret = real_recv(s, buf, len, flags);
	if (ret == -1 && errno != EAGAIN && errno != ENOBUFS) {
		swrap_dump_packet(si, NULL, SWRAP_RECV_RST, NULL, 0);
	} else if (ret == 0) { /* END OF FILE */
		swrap_dump_packet(si, NULL, SWRAP_RECV_RST, NULL, 0);
	} else {
		swrap_dump_packet(si, NULL, SWRAP_RECV, buf, ret);
	}

	return ret;
}