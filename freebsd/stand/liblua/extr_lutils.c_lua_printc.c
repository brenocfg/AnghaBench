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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 char* luaL_checklstring (int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int /*<<< orphan*/  putchar (unsigned char) ; 

__attribute__((used)) static int
lua_printc(lua_State *L)
{
	ssize_t cur, l;
	const char *s = luaL_checklstring(L, 1, &l);

	for (cur = 0; cur < l; ++cur)
		putchar((unsigned char)*(s++));

	return 1;
}