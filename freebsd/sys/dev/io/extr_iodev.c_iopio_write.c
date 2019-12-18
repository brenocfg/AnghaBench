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
struct iodev_pio_req {int width; int port; int val; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  iodev_write_1 (int,int) ; 
 int /*<<< orphan*/  iodev_write_2 (int,int) ; 
 int /*<<< orphan*/  iodev_write_4 (int,int) ; 

__attribute__((used)) static int
iopio_write(struct iodev_pio_req *req)
{

	switch (req->width) {
	case 1:
		iodev_write_1(req->port, req->val);
		break;
	case 2:
		if (req->port & 1) {
			iodev_write_1(req->port, req->val);
			iodev_write_1(req->port + 1, req->val >> 8);
		} else
			iodev_write_2(req->port, req->val);
		break;
	case 4:
		if (req->port & 1) {
			iodev_write_1(req->port, req->val);
			iodev_write_2(req->port + 1, req->val >> 8);
			iodev_write_1(req->port + 3, req->val >> 24);
		} else if (req->port & 2) {
			iodev_write_2(req->port, req->val);
			iodev_write_2(req->port + 2, req->val >> 16);
		} else
			iodev_write_4(req->port, req->val);
		break;
	default:
		return (EINVAL);
	}

	return (0);
}