#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ ud; } ;
struct TYPE_10__ {int type; TYPE_1__ value; int /*<<< orphan*/ * next; } ;
typedef  TYPE_2__ ucl_object_t ;
struct ucl_lua_funcdata {int /*<<< orphan*/  idx; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
#define  UCL_BOOLEAN 134 
#define  UCL_FLOAT 133 
#define  UCL_INT 132 
#define  UCL_NULL 131 
#define  UCL_STRING 130 
#define  UCL_TIME 129 
#define  UCL_USERDATA 128 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_obj_toboolean (TYPE_2__ const*) ; 
 int /*<<< orphan*/  ucl_obj_todouble (TYPE_2__ const*) ; 
 int /*<<< orphan*/  ucl_obj_toint (TYPE_2__ const*) ; 
 int /*<<< orphan*/  ucl_obj_tostring (TYPE_2__ const*) ; 
 int ucl_object_lua_push_array (int /*<<< orphan*/ *,TYPE_2__ const*) ; 

__attribute__((used)) static int
ucl_object_lua_push_scalar (lua_State *L, const ucl_object_t *obj,
		bool allow_array)
{
	struct ucl_lua_funcdata *fd;

	if (allow_array && obj->next != NULL) {
		/* Actually we need to push this as an array */
		return ucl_object_lua_push_array (L, obj);
	}

	switch (obj->type) {
	case UCL_BOOLEAN:
		lua_pushboolean (L, ucl_obj_toboolean (obj));
		break;
	case UCL_STRING:
		lua_pushstring (L, ucl_obj_tostring (obj));
		break;
	case UCL_INT:
#if LUA_VERSION_NUM >= 501
		lua_pushinteger (L, ucl_obj_toint (obj));
#else
		lua_pushnumber (L, ucl_obj_toint (obj));
#endif
		break;
	case UCL_FLOAT:
	case UCL_TIME:
		lua_pushnumber (L, ucl_obj_todouble (obj));
		break;
	case UCL_NULL:
		lua_getfield (L, LUA_REGISTRYINDEX, "ucl.null");
		break;
	case UCL_USERDATA:
		fd = (struct ucl_lua_funcdata *)obj->value.ud;
		lua_rawgeti (L, LUA_REGISTRYINDEX, fd->idx);
		break;
	default:
		lua_pushnil (L);
		break;
	}

	return 1;
}