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
 unsigned char sdio_readb (struct sdio_func*,unsigned int,int*) ; 

unsigned char sdio_f0_readb(struct sdio_func *func, unsigned int addr, int *err_ret) {
	return sdio_readb(func, addr, err_ret);
}