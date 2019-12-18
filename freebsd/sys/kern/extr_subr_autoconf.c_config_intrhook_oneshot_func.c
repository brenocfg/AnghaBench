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
struct oneshot_config_hook {int /*<<< orphan*/  och_hook; int /*<<< orphan*/  och_arg; int /*<<< orphan*/  (* och_func ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct oneshot_config_hook*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
config_intrhook_oneshot_func(void *arg)
{
	struct oneshot_config_hook *ohook;

	ohook = arg;
	ohook->och_func(ohook->och_arg);
	config_intrhook_disestablish(&ohook->och_hook);
	free(ohook, M_DEVBUF);
}