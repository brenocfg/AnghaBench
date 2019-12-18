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
struct sockaddr_un {int /*<<< orphan*/  sun_path; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID0set0 () ; 
 int /*<<< orphan*/  ID0setuser () ; 
 int /*<<< orphan*/  LogID0 ; 
 int bind (int,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int) ; 

int
ID0bind_un(int s, const struct sockaddr_un *name)
{
  int result;

  ID0set0();
  result = bind(s, (const struct sockaddr *)name, sizeof *name);
  log_Printf(LogID0, "%d = bind(%d, \"%s\", %d)\n",
            result, s, name->sun_path, (int)sizeof(*name));
  ID0setuser();
  return result;
}