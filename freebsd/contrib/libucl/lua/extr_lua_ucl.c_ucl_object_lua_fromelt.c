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
typedef  int /*<<< orphan*/  ucl_object_t ;
struct ucl_lua_funcdata {int /*<<< orphan*/  idx; int /*<<< orphan*/ * ret; int /*<<< orphan*/ * L; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  double int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
#define  LUA_TBOOLEAN 134 
#define  LUA_TFUNCTION 133 
#define  LUA_TNUMBER 132 
#define  LUA_TSTRING 131 
#define  LUA_TTABLE 130 
#define  LUA_TTHREAD 129 
#define  LUA_TUSERDATA 128 
 int /*<<< orphan*/  UCL_NULL ; 
 int /*<<< orphan*/  luaL_getmetafield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isfunction (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 double lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_topointer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_ucl_userdata_dtor ; 
 int /*<<< orphan*/  lua_ucl_userdata_emitter ; 
 struct ucl_lua_funcdata* malloc (int) ; 
 int /*<<< orphan*/  ucl_null ; 
 int /*<<< orphan*/ * ucl_object_frombool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ucl_object_fromdouble (double) ; 
 int /*<<< orphan*/ * ucl_object_fromint (double) ; 
 int /*<<< orphan*/ * ucl_object_fromstring_common (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ucl_object_lua_fromtable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ucl_object_new_userdata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * ucl_object_typed_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ucl_object_t *
ucl_object_lua_fromelt (lua_State *L, int idx)
{
	int type;
	double num;
	ucl_object_t *obj = NULL;
	struct ucl_lua_funcdata *fd;

	type = lua_type (L, idx);

	switch (type) {
	case LUA_TSTRING:
		obj = ucl_object_fromstring_common (lua_tostring (L, idx), 0, 0);
		break;
	case LUA_TNUMBER:
		num = lua_tonumber (L, idx);
		if (num == (int64_t)num) {
			obj = ucl_object_fromint (num);
		}
		else {
			obj = ucl_object_fromdouble (num);
		}
		break;
	case LUA_TBOOLEAN:
		obj = ucl_object_frombool (lua_toboolean (L, idx));
		break;
	case LUA_TUSERDATA:
		if (lua_topointer (L, idx) == ucl_null) {
			obj = ucl_object_typed_new (UCL_NULL);
		}
		break;
	case LUA_TTABLE:
	case LUA_TFUNCTION:
	case LUA_TTHREAD:
		if (luaL_getmetafield (L, idx, "__gen_ucl")) {
			if (lua_isfunction (L, -1)) {
				lua_settop (L, 3); /* gen, obj, func */
				lua_insert (L, 1); /* func, gen, obj */
				lua_insert (L, 2); /* func, obj, gen */
				lua_call(L, 2, 1);
				obj = ucl_object_lua_fromelt (L, 1);
			}
			lua_pop (L, 2);
		}
		else {
			if (type == LUA_TTABLE) {
				obj = ucl_object_lua_fromtable (L, idx);
			}
			else if (type == LUA_TFUNCTION) {
				fd = malloc (sizeof (*fd));
				if (fd != NULL) {
					lua_pushvalue (L, idx);
					fd->L = L;
					fd->ret = NULL;
					fd->idx = luaL_ref (L, LUA_REGISTRYINDEX);

					obj = ucl_object_new_userdata (lua_ucl_userdata_dtor,
							lua_ucl_userdata_emitter, (void *)fd);
				}
			}
		}
		break;
	}

	return obj;
}