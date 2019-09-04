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
struct xz_buf {scalar_t__ in_pos; scalar_t__ in_size; int* in; } ;
struct rc_dec {scalar_t__ init_bytes_left; int code; } ;

/* Variables and functions */

__attribute__((used)) static char rc_read_init(struct rc_dec *rc, struct xz_buf *b)
{
	while (rc->init_bytes_left > 0) {
		if (b->in_pos == b->in_size)
			return 0;

		rc->code = (rc->code << 8) + b->in[b->in_pos++];
		--rc->init_bytes_left;
	}

	return 1;
}