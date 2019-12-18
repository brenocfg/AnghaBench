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

/* Variables and functions */
 int /*<<< orphan*/  ID0set0 () ; 
 int /*<<< orphan*/  ID0setuser () ; 
 int /*<<< orphan*/  LogID0 ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int,char const*) ; 
 int uu_unlock (char const*) ; 

int
ID0uu_unlock(const char *basettyname)
{
  int ret;

  ID0set0();
  ret = uu_unlock(basettyname);
  log_Printf(LogID0, "%d = uu_unlock(\"%s\")\n", ret, basettyname);
  ID0setuser();
  return ret;
}