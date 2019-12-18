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
struct sdio_func {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  sdio_writeb (struct sdio_func*,unsigned char,unsigned int,int*) ; 

void sdio_f0_writeb(struct sdio_func *func, unsigned char b,
		    unsigned int addr, int *err_ret)
{
	if (addr < 0xF0 || addr > 0xFF) {
		if (err_ret)
			*err_ret = -EINVAL;
		return;
	}
	sdio_writeb(func, b, addr, err_ret);
}