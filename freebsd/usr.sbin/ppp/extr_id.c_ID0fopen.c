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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ID0set0 () ; 
 int /*<<< orphan*/  ID0setuser () ; 
 int /*<<< orphan*/  LogID0 ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char const*,char const*) ; 

FILE *
ID0fopen(const char *path, const char *mode)
{
  FILE *ret;

  ID0set0();
  ret = fopen(path, mode);
  log_Printf(LogID0, "%p = fopen(\"%s\", \"%s\")\n", ret, path, mode);
  ID0setuser();
  return ret;
}