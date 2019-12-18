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
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  callout_free ; 
 int /*<<< orphan*/  callout_free_arg ; 
 int /*<<< orphan*/ * callout_free_func ; 
 int /*<<< orphan*/  callout_free_mutex ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
callout_free_load(module_t mod, int cmd, void *arg)
{
	int error;

	switch (cmd) {
	case MOD_LOAD:
		mtx_init(&callout_free_mutex, "callout_free", NULL, MTX_DEF);
		/*
		 * Do not pass CALLOUT_RETURNUNLOCKED so the callout
		 * subsystem will unlock the "destroyed" mutex.
		 */
		callout_init_mtx(&callout_free, &callout_free_mutex, 0);
		printf("callout_free_func = %p\n", callout_free_func);
		printf("callout_free_arg = %p\n", &callout_free_arg);
		callout_reset(&callout_free, hz/10, callout_free_func,
		    &callout_free_arg);
		error = 0;
		break;

	case MOD_UNLOAD:
		error = 0;
		break;

	default:
		error = EOPNOTSUPP;
		break;
	}

	return (error);
}