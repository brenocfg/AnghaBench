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
struct TYPE_3__ {scalar_t__ zri_curinstrs; scalar_t__ zri_maxinstrs; void* zri_timed_out; void* zri_canceled; int /*<<< orphan*/  zri_sync; } ;
typedef  TYPE_1__ zcp_run_info_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Debug ;

/* Variables and functions */
 void* B_TRUE ; 
 int /*<<< orphan*/  FORREAL ; 
 int /*<<< orphan*/  JUSTLOOKING ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  ZCP_RUN_INFO_KEY ; 
 scalar_t__ issig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 scalar_t__ zfs_lua_check_instrlimit_interval ; 

__attribute__((used)) static void
zcp_lua_counthook(lua_State *state, lua_Debug *ar)
{
	lua_getfield(state, LUA_REGISTRYINDEX, ZCP_RUN_INFO_KEY);
	zcp_run_info_t *ri = lua_touserdata(state, -1);

	/*
	 * Check if we were canceled while waiting for the
	 * txg to sync or from our open context thread
	 */
	if (ri->zri_canceled ||
	    (!ri->zri_sync && issig(JUSTLOOKING) && issig(FORREAL))) {
		ri->zri_canceled = B_TRUE;
		(void) lua_pushstring(state, "Channel program was canceled.");
		(void) lua_error(state);
	}

	/*
	 * Check how many instructions the channel program has
	 * executed so far, and compare against the limit.
	 */
	ri->zri_curinstrs += zfs_lua_check_instrlimit_interval;
	if (ri->zri_maxinstrs != 0 && ri->zri_curinstrs > ri->zri_maxinstrs) {
		ri->zri_timed_out = B_TRUE;
		(void) lua_pushstring(state,
		    "Channel program timed out.");
		(void) lua_error(state);
	}
}