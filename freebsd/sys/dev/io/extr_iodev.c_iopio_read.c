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
struct iodev_pio_req {int width; int val; int port; } ;

/* Variables and functions */
 int EINVAL ; 
 int iodev_read_1 (int) ; 
 int iodev_read_2 (int) ; 
 int iodev_read_4 (int) ; 

__attribute__((used)) static int
iopio_read(struct iodev_pio_req *req)
{

	switch (req->width) {
	case 1:
		req->val = iodev_read_1(req->port);
		break;
	case 2:
		if (req->port & 1) {
			req->val = iodev_read_1(req->port);
			req->val |= iodev_read_1(req->port + 1) << 8;
		} else
			req->val = iodev_read_2(req->port);
		break;
	case 4:
		if (req->port & 1) {
			req->val = iodev_read_1(req->port);
			req->val |= iodev_read_2(req->port + 1) << 8;
			req->val |= iodev_read_1(req->port + 3) << 24;
		} else if (req->port & 2) {
			req->val = iodev_read_2(req->port);
			req->val |= iodev_read_2(req->port + 2) << 16;
		} else
			req->val = iodev_read_4(req->port);
		break;
	default:
		return (EINVAL);
	}

	return (0);
}