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
struct cmdargs {int argn; int argc; int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 int LINE_LEN ; 
 int LibAliasProxyRule (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  la ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

int
nat_ProxyRule(struct cmdargs const *arg)
{
  char cmd[LINE_LEN];
  int f, pos;
  size_t len;

  if (arg->argn >= arg->argc)
    return -1;

  for (f = arg->argn, pos = 0; f < arg->argc; f++) {
    len = strlen(arg->argv[f]);
    if (sizeof cmd - pos < len + (len ? 1 : 0))
      break;
    if (len)
      cmd[pos++] = ' ';
    strcpy(cmd + pos, arg->argv[f]);
    pos += len;
  }

  return LibAliasProxyRule(la, cmd);
}