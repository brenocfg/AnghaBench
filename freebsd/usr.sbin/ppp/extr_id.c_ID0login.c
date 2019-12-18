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
struct utmpx {int /*<<< orphan*/  ut_host; int /*<<< orphan*/  ut_line; int /*<<< orphan*/  ut_user; int /*<<< orphan*/  ut_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID0set0 () ; 
 int /*<<< orphan*/  ID0setuser () ; 
 int /*<<< orphan*/  LogID0 ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pututxline (struct utmpx const*) ; 

void
ID0login(const struct utmpx *ut)
{
  ID0set0();
  pututxline(ut);
  log_Printf(LogID0, "pututxline(\"%.*s\", \"%.*s\", \"%.*s\", \"%.*s\")\n",
      (int)sizeof ut->ut_id, ut->ut_id,
      (int)sizeof ut->ut_user, ut->ut_user,
      (int)sizeof ut->ut_line, ut->ut_line,
      (int)sizeof ut->ut_host, ut->ut_host);
  ID0setuser();
}