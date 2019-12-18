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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EINVAL ; 
#define  MOD_LOAD 131 
#define  MOD_QUIESCE 130 
#define  MOD_SHUTDOWN 129 
#define  MOD_UNLOAD 128 
 int deinit_siftr () ; 
 int init_siftr () ; 

__attribute__((used)) static int
siftr_load_handler(module_t mod, int what, void *arg)
{
	int ret;

	switch (what) {
	case MOD_LOAD:
		ret = init_siftr();
		break;

	case MOD_QUIESCE:
	case MOD_SHUTDOWN:
		ret = deinit_siftr();
		break;

	case MOD_UNLOAD:
		ret = 0;
		break;

	default:
		ret = EINVAL;
		break;
	}

	return (ret);
}