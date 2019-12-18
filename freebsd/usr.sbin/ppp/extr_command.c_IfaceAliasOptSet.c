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
struct cmdargs {TYPE_2__* bundle; } ;
struct TYPE_3__ {unsigned long long optmask; } ;
struct TYPE_4__ {TYPE_1__ cfg; int /*<<< orphan*/  NatEnabled; } ;

/* Variables and functions */
 scalar_t__ Enabled (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  OPT_IFACEALIAS ; 
 int OptSet (struct cmdargs const*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
IfaceAliasOptSet(struct cmdargs const *arg)
{
  unsigned long long save = arg->bundle->cfg.optmask;
  int result = OptSet(arg);

  if (result == 0)
    if (Enabled(arg->bundle, OPT_IFACEALIAS) && !arg->bundle->NatEnabled) {
      arg->bundle->cfg.optmask = save;
      log_Printf(LogWARN, "Cannot enable iface-alias without NAT\n");
      result = 2;
    }

  return result;
}