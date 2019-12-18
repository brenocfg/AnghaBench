#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cmdargs {int argn; int /*<<< orphan*/  bundle; int /*<<< orphan*/ * argv; TYPE_1__* cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  ipv6_available; } ;
struct TYPE_3__ {scalar_t__ args; } ;

/* Variables and functions */
 int /*<<< orphan*/  Enabled (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LogWARN ; 
 unsigned int NEG_ENABLED ; 
 int OPT_IPV6CP ; 
 int OPT_NAS_IDENTIFIER ; 
 int OPT_NAS_IP_ADDRESS ; 
 int /*<<< orphan*/ * ident_cmd (int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  opt_disable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opt_enable (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ probe ; 

__attribute__((used)) static int
OptSet(struct cmdargs const *arg)
{
  int opt = (int)(long)arg->cmd->args;
  unsigned keep;			/* Keep this opt */
  unsigned add;				/* Add this opt */

  if (ident_cmd(arg->argv[arg->argn - 2], &keep, &add) == NULL)
    return 1;

#ifndef NOINET6
  if (add == NEG_ENABLED && opt == OPT_IPV6CP && !probe.ipv6_available) {
    log_Printf(LogWARN, "IPv6 is not available on this machine\n");
    return 1;
  }
#endif
  if (!add && ((opt == OPT_NAS_IP_ADDRESS &&
                !Enabled(arg->bundle, OPT_NAS_IDENTIFIER)) ||
               (opt == OPT_NAS_IDENTIFIER &&
                !Enabled(arg->bundle, OPT_NAS_IP_ADDRESS)))) {
    log_Printf(LogWARN,
               "Cannot disable both NAS-IP-Address and NAS-Identifier\n");
    return 1;
  }

  if (add)
    opt_enable(arg->bundle, opt);
  else
    opt_disable(arg->bundle, opt);

  return 0;
}