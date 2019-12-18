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
struct TYPE_2__ {int /*<<< orphan*/  mtu; } ;
struct ldc_channel {int mssbuf_len; scalar_t__ mssbuf_off; scalar_t__ mssbuf; TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,scalar_t__,unsigned int) ; 
 int read_nonraw (struct ldc_channel*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_stream(struct ldc_channel *lp, void *buf, unsigned int size)
{
	if (!lp->mssbuf_len) {
		int err = read_nonraw(lp, lp->mssbuf, lp->cfg.mtu);
		if (err < 0)
			return err;

		lp->mssbuf_len = err;
		lp->mssbuf_off = 0;
	}

	if (size > lp->mssbuf_len)
		size = lp->mssbuf_len;
	memcpy(buf, lp->mssbuf + lp->mssbuf_off, size);

	lp->mssbuf_off += size;
	lp->mssbuf_len -= size;

	return size;
}