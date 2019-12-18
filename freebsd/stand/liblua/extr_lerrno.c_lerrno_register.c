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
struct TYPE_3__ {int /*<<< orphan*/  err_name; int /*<<< orphan*/  err_num; } ;

/* Variables and functions */
 TYPE_1__* errnoconstants ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 size_t nitems (TYPE_1__*) ; 

__attribute__((used)) static void
lerrno_register(lua_State *L)
{
	size_t i;

	for (i = 0; i < nitems(errnoconstants); i++) {
		lua_pushinteger(L, errnoconstants[i].err_num);
		lua_setfield(L, -2, errnoconstants[i].err_name);
	}
}