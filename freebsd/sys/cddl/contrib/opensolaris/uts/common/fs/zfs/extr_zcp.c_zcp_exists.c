#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * zri_pool; } ;
typedef  TYPE_1__ zcp_run_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  kwargs; int /*<<< orphan*/  pargs; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ zcp_lib_info_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int EIO ; 
 int ENOENT ; 
 int EXDEV ; 
 int /*<<< orphan*/  FTAG ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 TYPE_2__ zcp_exists_info ; 
 int /*<<< orphan*/  zcp_parse_args (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* zcp_run_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zcp_exists(lua_State *state)
{
	zcp_run_info_t *ri = zcp_run_info(state);
	dsl_pool_t *dp = ri->zri_pool;
	zcp_lib_info_t *libinfo = &zcp_exists_info;

	zcp_parse_args(state, libinfo->name, libinfo->pargs, libinfo->kwargs);

	const char *dsname = lua_tostring(state, 1);

	dsl_dataset_t *ds;
	int error = dsl_dataset_hold(dp, dsname, FTAG, &ds);
	if (error == 0) {
		dsl_dataset_rele(ds, FTAG);
		lua_pushboolean(state, B_TRUE);
	} else if (error == ENOENT) {
		lua_pushboolean(state, B_FALSE);
	} else if (error == EXDEV) {
		return (luaL_error(state, "dataset '%s' is not in the "
		    "target pool", dsname));
	} else if (error == EIO) {
		return (luaL_error(state, "I/O error opening dataset '%s'",
		    dsname));
	} else if (error != 0) {
		return (luaL_error(state, "unexpected error %d", error));
	}

	return (1);
}