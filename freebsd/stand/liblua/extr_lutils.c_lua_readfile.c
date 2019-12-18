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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {size_t size; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 size_t fread (char*,int,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_tonumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int) ; 
 scalar_t__ malloc (size_t) ; 

__attribute__((used)) static int
lua_readfile(lua_State *L)
{
	FILE	**f;
	size_t	size, r;
	char * buf;

	if (lua_gettop(L) < 1 || lua_gettop(L) > 2) {
		lua_pushnil(L);
		lua_pushinteger(L, 0);
		return 2;
	}

	f = (FILE**)lua_touserdata(L, 1);

	if (f == NULL || *f == NULL) {
		lua_pushnil(L);
		lua_pushinteger(L, 0);
		return 2;
	}

	if (lua_gettop(L) == 2)
		size = (size_t)lua_tonumber(L, 2);
	else
		size = (*f)->size;


	buf = (char*)malloc(size);
	r = fread(buf, 1, size, *f);
	lua_pushlstring(L, buf, r);
	free(buf);
	lua_pushinteger(L, r);

	return 2;
}