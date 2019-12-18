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

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOBUFS ; 
#define  FIONREAD 128 
 int /*<<< orphan*/  SWRAP_PENDING_RST ; 
 int /*<<< orphan*/  errno ; 
 struct socket_info* find_socket_info (int) ; 
 int real_ioctl (int,int,void*) ; 
 int /*<<< orphan*/  swrap_dump_packet (struct socket_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int swrap_ioctl(int s, int r, void *p)
{
	int ret;
	struct socket_info *si = find_socket_info(s);
	int value;

	if (!si) {
		return real_ioctl(s, r, p);
	}

	ret = real_ioctl(s, r, p);

	switch (r) {
	case FIONREAD:
		value = *((int *)p);
		if (ret == -1 && errno != EAGAIN && errno != ENOBUFS) {
			swrap_dump_packet(si, NULL, SWRAP_PENDING_RST, NULL, 0);
		} else if (value == 0) { /* END OF FILE */
			swrap_dump_packet(si, NULL, SWRAP_PENDING_RST, NULL, 0);
		}
		break;
	}

	return ret;
}