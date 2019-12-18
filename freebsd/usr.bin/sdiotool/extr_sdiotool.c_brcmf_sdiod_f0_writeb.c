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
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  u8 ;
struct sdio_func {int dummy; } ;

/* Variables and functions */
 scalar_t__ SDIO_CCCR_ABORT ; 
 scalar_t__ SDIO_CCCR_IENx ; 
 int /*<<< orphan*/  sdio_f0_writeb (struct sdio_func*,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  sdio_writeb (struct sdio_func*,int /*<<< orphan*/ ,scalar_t__,int*) ; 

__attribute__((used)) static inline int brcmf_sdiod_f0_writeb(struct sdio_func *func,
					uint regaddr, u8 byte) {
	int err_ret;

	/*
	 * Can only directly write to some F0 registers.
	 * Handle CCCR_IENx and CCCR_ABORT command
	 * as a special case.
	 */
	if ((regaddr == SDIO_CCCR_ABORT) ||
	    (regaddr == SDIO_CCCR_IENx))
		sdio_writeb(func, byte, regaddr, &err_ret);
	else
		sdio_f0_writeb(func, byte, regaddr, &err_ret);

	return err_ret;
}