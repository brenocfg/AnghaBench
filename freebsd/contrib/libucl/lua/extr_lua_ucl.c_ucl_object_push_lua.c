#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type; } ;
typedef  TYPE_1__ ucl_object_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  UCL_ARRAY 129 
#define  UCL_OBJECT 128 
 int ucl_object_lua_push_array (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int ucl_object_lua_push_object (int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 
 int ucl_object_lua_push_scalar (int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 

int
ucl_object_push_lua (lua_State *L, const ucl_object_t *obj, bool allow_array)
{
	switch (obj->type) {
	case UCL_OBJECT:
		return ucl_object_lua_push_object (L, obj, allow_array);
	case UCL_ARRAY:
		return ucl_object_lua_push_array (L, obj);
	default:
		return ucl_object_lua_push_scalar (L, obj, allow_array);
	}
}