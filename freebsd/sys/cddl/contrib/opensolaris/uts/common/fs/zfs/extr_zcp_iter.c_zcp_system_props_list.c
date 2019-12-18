#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kwargs; int /*<<< orphan*/  pargs; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zcp_list_info_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
struct TYPE_5__ {int /*<<< orphan*/ * zri_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int luaL_error (int /*<<< orphan*/ *,char*,char*) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zcp_dataset_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcp_dataset_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zcp_nvlist_to_lua (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  zcp_parse_args (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* zcp_run_info (int /*<<< orphan*/ *) ; 
 TYPE_1__ zcp_system_props_list_info ; 

__attribute__((used)) static int
zcp_system_props_list(lua_State *state)
{
	int error;
	char errbuf[128];
	const char *dataset_name;
	dsl_pool_t *dp = zcp_run_info(state)->zri_pool;
	zcp_list_info_t *libinfo = &zcp_system_props_list_info;
	zcp_parse_args(state, libinfo->name, libinfo->pargs, libinfo->kwargs);
	dataset_name = lua_tostring(state, 1);
	nvlist_t *nv = fnvlist_alloc();

	dsl_dataset_t *ds = zcp_dataset_hold(state, dp, dataset_name, FTAG);
	if (ds == NULL)
		return (1); /* not reached; zcp_dataset_hold() longjmp'd */

	/* Get the names of all valid properties for this dataset */
	zcp_dataset_props(ds, nv);
	dsl_dataset_rele(ds, FTAG);

	/* push list as lua table */
	error = zcp_nvlist_to_lua(state, nv, errbuf, sizeof (errbuf));
	nvlist_free(nv);
	if (error != 0) {
		return (luaL_error(state,
		    "Error returning nvlist: %s", errbuf));
	}
	return (1);
}