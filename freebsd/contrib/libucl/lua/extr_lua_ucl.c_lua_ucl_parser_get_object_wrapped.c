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
struct ucl_parser {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 struct ucl_parser* lua_ucl_parser_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_ucl_push_opaque (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ucl_parser_get_object (struct ucl_parser*) ; 

__attribute__((used)) static int
lua_ucl_parser_get_object_wrapped (lua_State *L)
{
	struct ucl_parser *parser;
	ucl_object_t *obj;
	int ret = 1;

	parser = lua_ucl_parser_get (L, 1);
	obj = ucl_parser_get_object (parser);

	if (obj != NULL) {
		lua_ucl_push_opaque (L, obj);
	}
	else {
		lua_pushnil (L);
	}

	return ret;
}