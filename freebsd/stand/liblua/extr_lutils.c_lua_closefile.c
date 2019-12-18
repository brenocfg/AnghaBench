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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lua_closefile(lua_State *L)
{
	FILE ** f;
	if (lua_gettop(L) != 1) {
		lua_pushboolean(L, 0);
		return 1;
	}

	f = (FILE**)lua_touserdata(L, 1);
	if (f != NULL && *f != NULL) {
		lua_pushboolean(L, fclose(*f) == 0 ? 1 : 0);
		*f = NULL;
	} else
		lua_pushboolean(L, 0);

	return 1;
}