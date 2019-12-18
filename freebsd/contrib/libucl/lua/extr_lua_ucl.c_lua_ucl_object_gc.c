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
 int /*<<< orphan*/ * lua_ucl_object_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ucl_object_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lua_ucl_object_gc (lua_State *L)
{
	ucl_object_t *obj;

	obj = lua_ucl_object_get (L, 1);

	ucl_object_unref (obj);

	return 0;
}