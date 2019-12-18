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
typedef  int /*<<< orphan*/  ShellState ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int lintFkeyIndexes (int /*<<< orphan*/ *,char**,int) ; 
 int /*<<< orphan*/  raw_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ sqlite3_strnicmp (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen30 (char*) ; 

__attribute__((used)) static int lintDotCommand(
  ShellState *pState,             /* Current shell tool state */
  char **azArg,                   /* Array of arguments passed to dot command */
  int nArg                        /* Number of entries in azArg[] */
){
  int n;
  n = (nArg>=2 ? strlen30(azArg[1]) : 0);
  if( n<1 || sqlite3_strnicmp(azArg[1], "fkey-indexes", n) ) goto usage;
  return lintFkeyIndexes(pState, azArg, nArg);

 usage:
  raw_printf(stderr, "Usage %s sub-command ?switches...?\n", azArg[0]);
  raw_printf(stderr, "Where sub-commands are:\n");
  raw_printf(stderr, "    fkey-indexes\n");
  return SQLITE_ERROR;
}