#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ start; scalar_t__ ptr; } ;
struct TYPE_3__ {TYPE_2__ buf; } ;
struct lanai_vcc {TYPE_1__ tx; } ;

/* Variables and functions */
 scalar_t__ lanai_buf_size (TYPE_2__*) ; 

__attribute__((used)) static inline int vcc_tx_space(const struct lanai_vcc *lvcc, int endptr)
{
	int r;
	r = endptr * 16;
	r -= ((unsigned long) lvcc->tx.buf.ptr) -
	    ((unsigned long) lvcc->tx.buf.start);
	r -= 16;	/* Leave "bubble" - if start==end it looks empty */
	if (r < 0)
		r += lanai_buf_size(&lvcc->tx.buf);
	return r;
}