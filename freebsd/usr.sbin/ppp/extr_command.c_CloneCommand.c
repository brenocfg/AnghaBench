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
struct cmdargs {int argc; int argn; int /*<<< orphan*/  cx; int /*<<< orphan*/  bundle; int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 int LINE_LEN ; 
 int /*<<< orphan*/  bundle_DatalinkClone (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static int
CloneCommand(struct cmdargs const *arg)
{
  char namelist[LINE_LEN];
  char *name;
  int f;

  if (arg->argc == arg->argn)
    return -1;

  namelist[sizeof namelist - 1] = '\0';
  for (f = arg->argn; f < arg->argc; f++) {
    strncpy(namelist, arg->argv[f], sizeof namelist - 1);
    for(name = strtok(namelist, ", "); name; name = strtok(NULL,", "))
      bundle_DatalinkClone(arg->bundle, arg->cx, name);
  }

  return 0;
}