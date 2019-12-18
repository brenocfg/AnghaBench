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
typedef  enum ucl_emitter { ____Placeholder_ucl_emitter } ucl_emitter ;

/* Variables and functions */
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 unsigned char* ucl_object_emit (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
lua_ucl_to_string (lua_State *L, const ucl_object_t *obj, enum ucl_emitter type)
{
	unsigned char *result;

	result = ucl_object_emit (obj, type);

	if (result != NULL) {
		lua_pushstring (L, (const char *)result);
		free (result);
	}
	else {
		lua_pushnil (L);
	}

	return 1;
}