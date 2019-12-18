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
struct TYPE_2__ {struct oneshot_config_hook* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct oneshot_config_hook {TYPE_1__ och_hook; void* och_arg; int /*<<< orphan*/  och_func; } ;
typedef  int /*<<< orphan*/  ich_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  config_intrhook_establish (TYPE_1__*) ; 
 int /*<<< orphan*/  config_intrhook_oneshot_func ; 
 struct oneshot_config_hook* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
config_intrhook_oneshot(ich_func_t func, void *arg)
{
	struct oneshot_config_hook *ohook;

	ohook = malloc(sizeof(*ohook), M_DEVBUF, M_WAITOK);
	ohook->och_func = func;
	ohook->och_arg  = arg;
	ohook->och_hook.ich_func = config_intrhook_oneshot_func;
	ohook->och_hook.ich_arg  = ohook;
	config_intrhook_establish(&ohook->och_hook);
}