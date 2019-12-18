#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct cmdargs {int argc; int argn; TYPE_4__* bundle; int /*<<< orphan*/ * argv; } ;
struct TYPE_5__ {scalar_t__ state; } ;
struct TYPE_6__ {int /*<<< orphan*/  my_ip; TYPE_1__ fsm; } ;
struct TYPE_7__ {TYPE_2__ ipcp; } ;
struct TYPE_8__ {int NatEnabled; TYPE_3__ ncp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LibAliasSetAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPT_IFACEALIAS ; 
 scalar_t__ ST_OPENED ; 
 int /*<<< orphan*/  la ; 
 int /*<<< orphan*/  opt_disable (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
NatEnable(struct cmdargs const *arg)
{
  if (arg->argc == arg->argn+1) {
    if (strcasecmp(arg->argv[arg->argn], "yes") == 0) {
      if (!arg->bundle->NatEnabled) {
        if (arg->bundle->ncp.ipcp.fsm.state == ST_OPENED)
          LibAliasSetAddress(la, arg->bundle->ncp.ipcp.my_ip);
        arg->bundle->NatEnabled = 1;
      }
      return 0;
    } else if (strcasecmp(arg->argv[arg->argn], "no") == 0) {
      arg->bundle->NatEnabled = 0;
      opt_disable(arg->bundle, OPT_IFACEALIAS);
      /* Don't iface_Clear() - there may be manually configured addresses */
      return 0;
    }
  }

  return -1;
}