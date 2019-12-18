#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* zri_tx; } ;
typedef  TYPE_2__ zcp_run_info_t ;
struct TYPE_8__ {int /*<<< orphan*/  kwargs; int /*<<< orphan*/  pargs; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ zcp_lib_info_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {int /*<<< orphan*/  tx_txg; } ;

/* Variables and functions */
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 TYPE_3__ zcp_debug_info ; 
 int /*<<< orphan*/  zcp_parse_args (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* zcp_run_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
zcp_debug(lua_State *state)
{
	const char *dbgstring;
	zcp_run_info_t *ri = zcp_run_info(state);
	zcp_lib_info_t *libinfo = &zcp_debug_info;

	zcp_parse_args(state, libinfo->name, libinfo->pargs, libinfo->kwargs);

	dbgstring = lua_tostring(state, 1);

	zfs_dbgmsg("txg %lld ZCP: %s", ri->zri_tx->tx_txg, dbgstring);

	return (0);
}