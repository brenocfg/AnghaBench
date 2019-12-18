#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * next; } ;
typedef  TYPE_1__ ucl_object_t ;
typedef  int /*<<< orphan*/ * ucl_object_iter_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ucl_object_iterate (TYPE_1__ const*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  ucl_object_key (TYPE_1__ const*) ; 
 int ucl_object_lua_push_array (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  ucl_object_lua_push_element (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__ const*) ; 

__attribute__((used)) static int
ucl_object_lua_push_object (lua_State *L, const ucl_object_t *obj,
		bool allow_array)
{
	const ucl_object_t *cur;
	ucl_object_iter_t it = NULL;
	int nelt = 0;

	if (allow_array && obj->next != NULL) {
		/* Actually we need to push this as an array */
		return ucl_object_lua_push_array (L, obj);
	}

	/* Optimize allocation by preallocation of table */
	while (ucl_object_iterate (obj, &it, true) != NULL) {
		nelt ++;
	}

	lua_createtable (L, 0, nelt);
	it = NULL;

	while ((cur = ucl_object_iterate (obj, &it, true)) != NULL) {
		ucl_object_lua_push_element (L, ucl_object_key (cur), cur);
	}

	return 1;
}