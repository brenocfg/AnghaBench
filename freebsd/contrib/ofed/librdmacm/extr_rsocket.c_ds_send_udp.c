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
typedef  int /*<<< orphan*/  uint8_t ;
struct rsocket {int dummy; } ;
struct iovec {size_t iov_len; void* iov_base; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ds_sendv_udp (struct rsocket*,struct iovec*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ds_send_udp(struct rsocket *rs, const void *buf, size_t len,
			   int flags, uint8_t op)
{
	struct iovec iov;
	if (buf && len) {
		iov.iov_base = (void *) buf;
		iov.iov_len = len;
		return ds_sendv_udp(rs, &iov, 1, flags, op);
	} else {
		return ds_sendv_udp(rs, NULL, 0, flags, op);
	}
}