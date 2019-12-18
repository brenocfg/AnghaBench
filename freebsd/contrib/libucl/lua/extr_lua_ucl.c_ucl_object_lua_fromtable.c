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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int INT_MIN ; 
 scalar_t__ LUA_TNUMBER ; 
 int /*<<< orphan*/  UCL_ARRAY ; 
 int /*<<< orphan*/  UCL_OBJECT ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 double lua_tonumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ucl_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucl_object_insert_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,size_t,int) ; 
 int /*<<< orphan*/ * ucl_object_lua_fromelt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ucl_object_typed_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ucl_object_t *
ucl_object_lua_fromtable (lua_State *L, int idx)
{
	ucl_object_t *obj, *top = NULL;
	size_t keylen;
	const char *k;
	bool is_array = true;
	int max = INT_MIN;

	if (idx < 0) {
		/* For negative indicies we want to invert them */
		idx = lua_gettop (L) + idx + 1;
	}
	/* Check for array */
	lua_pushnil (L);
	while (lua_next (L, idx) != 0) {
		if (lua_type (L, -2) == LUA_TNUMBER) {
			double num = lua_tonumber (L, -2);
			if (num == (int)num) {
				if (num > max) {
					max = num;
				}
			}
			else {
				/* Keys are not integer */
				lua_pop (L, 2);
				is_array = false;
				break;
			}
		}
		else {
			/* Keys are not numeric */
			lua_pop (L, 2);
			is_array = false;
			break;
		}
		lua_pop (L, 1);
	}

	/* Table iterate */
	if (is_array) {
		int i;

		top = ucl_object_typed_new (UCL_ARRAY);
		for (i = 1; i <= max; i ++) {
			lua_pushinteger (L, i);
			lua_gettable (L, idx);
			obj = ucl_object_lua_fromelt (L, lua_gettop (L));
			if (obj != NULL) {
				ucl_array_append (top, obj);
			}
			lua_pop (L, 1);
		}
	}
	else {
		lua_pushnil (L);
		top = ucl_object_typed_new (UCL_OBJECT);
		while (lua_next (L, idx) != 0) {
			/* copy key to avoid modifications */
			k = lua_tolstring (L, -2, &keylen);
			obj = ucl_object_lua_fromelt (L, lua_gettop (L));

			if (obj != NULL) {
				ucl_object_insert_key (top, obj, k, keylen, true);
			}
			lua_pop (L, 1);
		}
	}

	return top;
}