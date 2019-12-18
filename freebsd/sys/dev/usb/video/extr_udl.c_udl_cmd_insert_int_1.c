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
struct udl_cmd_buf {size_t off; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */

__attribute__((used)) static void
udl_cmd_insert_int_1(struct udl_cmd_buf *cb, uint8_t value)
{

	cb->buf[cb->off] = value;
	cb->off += 1;
}