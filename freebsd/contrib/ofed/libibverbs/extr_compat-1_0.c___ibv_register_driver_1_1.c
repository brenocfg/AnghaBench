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
typedef  int /*<<< orphan*/  ibv_driver_init_func_1_1 ;

/* Variables and functions */

void __ibv_register_driver_1_1(const char *name, ibv_driver_init_func_1_1 init_func)
{
	/* The driver interface is private as of rdma-core 13. This stub is
	 * left to preserve dynamic-link compatibility with old libfabrics
	 * usnic providers which use this function only to suppress a fprintf
	 * in old versions of libibverbs. */
}