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
struct interp_lua_softc {int /*<<< orphan*/  luap; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDBG (char*,char const*) ; 
 int luaL_dofile (int /*<<< orphan*/ ,char const*) ; 
 struct interp_lua_softc lua_softc ; 

int
interp_include(const char *filename)
{
	struct interp_lua_softc	*softc = &lua_softc;

	LDBG("loading file %s", filename);

	return (luaL_dofile(softc->luap, filename));
}