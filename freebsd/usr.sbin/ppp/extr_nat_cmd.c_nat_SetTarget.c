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
struct in_addr {scalar_t__ s_addr; } ;
struct cmdargs {int argc; int argn; int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 struct in_addr GetIpAddr (int /*<<< orphan*/ ) ; 
 void* INADDR_ANY ; 
 scalar_t__ INADDR_NONE ; 
 int /*<<< orphan*/  LibAliasSetTarget (int /*<<< orphan*/ ,struct in_addr) ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  la ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 

int
nat_SetTarget(struct cmdargs const *arg)
{
  struct in_addr addr;

  if (arg->argc == arg->argn) {
    addr.s_addr = INADDR_ANY;
    LibAliasSetTarget(la, addr);
    return 0;
  }

  if (arg->argc != arg->argn + 1)
    return -1;

  if (!strcasecmp(arg->argv[arg->argn], "MYADDR")) {
    addr.s_addr = INADDR_ANY;
    LibAliasSetTarget(la, addr);
    return 0;
  }

  addr = GetIpAddr(arg->argv[arg->argn]);
  if (addr.s_addr == INADDR_NONE) {
    log_Printf(LogWARN, "%s: invalid address\n", arg->argv[arg->argn]);
    return 1;
  }

  LibAliasSetTarget(la, addr);
  return 0;
}