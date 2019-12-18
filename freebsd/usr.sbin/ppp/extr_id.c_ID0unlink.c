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
 int unlink (char const*) ; 

int
ID0unlink(const char *name)
{
  int ret;

  ID0set0();
  ret = unlink(name);
  log_Printf(LogID0, "%d = unlink(\"%s\")\n", ret, name);
  ID0setuser();
  return ret;
}