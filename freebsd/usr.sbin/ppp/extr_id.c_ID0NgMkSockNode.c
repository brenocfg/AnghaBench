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
 int NgMkSockNode (char const*,int*,int*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int,char const*) ; 

int
ID0NgMkSockNode(const char *name, int *cs, int *ds)
{
  int result;

  ID0set0();
  result = NgMkSockNode(name, cs, ds);
  log_Printf(LogID0, "%d = NgMkSockNode(\"%s\", &cs, &ds)\n",
             result, name ? name : "");
  ID0setuser();
  return result;
}