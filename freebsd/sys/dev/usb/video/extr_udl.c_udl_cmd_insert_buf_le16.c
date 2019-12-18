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
typedef  int uint32_t ;
struct udl_cmd_buf {int off; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */

__attribute__((used)) static void
udl_cmd_insert_buf_le16(struct udl_cmd_buf *cb, const uint8_t *buf, uint32_t len)
{
	uint32_t x;

	for (x = 0; x != len; x += 2) {
		/* byte swap from little endian to big endian */
		cb->buf[cb->off + x + 0] = buf[x + 1];
		cb->buf[cb->off + x + 1] = buf[x + 0];
	}
	cb->off += len;
}