#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  zri_cleanup_handlers; } ;
typedef  TYPE_1__ zcp_run_info_t ;
typedef  int /*<<< orphan*/  zcp_cleanup_t ;
struct TYPE_8__ {void* zch_cleanup_arg; int /*<<< orphan*/  zch_cleanup_func; } ;
typedef  TYPE_2__ zcp_cleanup_handler_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 TYPE_2__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_insert_head (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_1__* zcp_run_info (int /*<<< orphan*/ *) ; 

zcp_cleanup_handler_t *
zcp_register_cleanup(lua_State *state, zcp_cleanup_t cleanfunc, void *cleanarg)
{
	zcp_run_info_t *ri = zcp_run_info(state);

	zcp_cleanup_handler_t *zch = kmem_alloc(sizeof (*zch), KM_SLEEP);
	zch->zch_cleanup_func = cleanfunc;
	zch->zch_cleanup_arg = cleanarg;
	list_insert_head(&ri->zri_cleanup_handlers, zch);

	return (zch);
}