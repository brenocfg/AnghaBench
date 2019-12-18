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
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lua_dir_iter_close(lua_State *L)
{
	DIR *dp, **dpp;

	dpp = (DIR **)lua_touserdata(L, 1);
	dp = *dpp;
	if (dp == NULL)
		return 0;

	closedir(dp);
	*dpp = NULL;
	return 0;
}