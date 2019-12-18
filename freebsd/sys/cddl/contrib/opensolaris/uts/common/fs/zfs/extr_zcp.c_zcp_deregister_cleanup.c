#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  zri_cleanup_handlers; } ;
typedef  TYPE_1__ zcp_run_info_t ;
typedef  int /*<<< orphan*/  zcp_cleanup_handler_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* zcp_run_info (int /*<<< orphan*/ *) ; 

void
zcp_deregister_cleanup(lua_State *state, zcp_cleanup_handler_t *zch)
{
	zcp_run_info_t *ri = zcp_run_info(state);
	list_remove(&ri->zri_cleanup_handlers, zch);
	kmem_free(zch, sizeof (*zch));
}