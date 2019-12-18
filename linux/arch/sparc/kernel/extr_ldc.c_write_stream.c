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
struct TYPE_2__ {unsigned int mtu; } ;
struct ldc_channel {TYPE_1__ cfg; } ;

/* Variables and functions */
 int write_nonraw (struct ldc_channel*,void const*,unsigned int) ; 

__attribute__((used)) static int write_stream(struct ldc_channel *lp, const void *buf,
			unsigned int size)
{
	if (size > lp->cfg.mtu)
		size = lp->cfg.mtu;
	return write_nonraw(lp, buf, size);
}