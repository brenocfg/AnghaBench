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
typedef  int /*<<< orphan*/  u_int8_t ;
struct ber {int /*<<< orphan*/ * br_rend; void* br_rptr; void* br_rbuf; } ;

/* Variables and functions */

void
ber_set_readbuf(struct ber *b, void *buf, size_t len)
{
	b->br_rbuf = b->br_rptr = buf;
	b->br_rend = (u_int8_t *)buf + len;
}