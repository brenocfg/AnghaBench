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
struct passwd {char* pw_name; } ;
struct cmdargs {int argn; int argc; int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID0realuid () ; 
 int /*<<< orphan*/  endpwent () ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int userok ; 

int
AllowUsers(struct cmdargs const *arg)
{
  /* arg->bundle may be NULL (see system_IsValid()) ! */
  int f;
  struct passwd *pwd;

  if (userok == -1)
    userok = 0;

  pwd = getpwuid(ID0realuid());
  if (pwd != NULL)
    for (f = arg->argn; f < arg->argc; f++)
      if (!strcmp("*", arg->argv[f]) || !strcmp(pwd->pw_name, arg->argv[f])) {
        userok = 1;
        break;
      }
  endpwent();

  return 0;
}