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
typedef  int /*<<< orphan*/  zcp_arg_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zcp_parse_pos_args (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  zcp_parse_table_args (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

void
zcp_parse_args(lua_State *state, const char *fname, const zcp_arg_t *pargs,
    const zcp_arg_t *kwargs)
{
	if (lua_gettop(state) == 1 && lua_istable(state, 1)) {
		zcp_parse_table_args(state, fname, pargs, kwargs);
	} else {
		zcp_parse_pos_args(state, fname, pargs, kwargs);
	}
}