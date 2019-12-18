#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct cmdargs {int argc; int argn; TYPE_3__* bundle; int /*<<< orphan*/ * argv; } ;
struct TYPE_7__ {int writable; } ;
struct TYPE_10__ {TYPE_1__ ns; } ;
struct TYPE_8__ {TYPE_4__ ipcp; } ;
struct TYPE_9__ {TYPE_2__ ncp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipcp_LoadDNS (TYPE_4__*) ; 
 int /*<<< orphan*/  ipcp_RestoreDNS (TYPE_4__*) ; 
 int /*<<< orphan*/  ipcp_WriteDNS (TYPE_4__*) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ResolvCommand(struct cmdargs const *arg)
{
  if (arg->argc == arg->argn + 1) {
    if (!strcasecmp(arg->argv[arg->argn], "reload"))
      ipcp_LoadDNS(&arg->bundle->ncp.ipcp);
    else if (!strcasecmp(arg->argv[arg->argn], "restore"))
      ipcp_RestoreDNS(&arg->bundle->ncp.ipcp);
    else if (!strcasecmp(arg->argv[arg->argn], "rewrite"))
      ipcp_WriteDNS(&arg->bundle->ncp.ipcp);
    else if (!strcasecmp(arg->argv[arg->argn], "readonly"))
      arg->bundle->ncp.ipcp.ns.writable = 0;
    else if (!strcasecmp(arg->argv[arg->argn], "writable"))
      arg->bundle->ncp.ipcp.ns.writable = 1;
    else
      return -1;

    return 0;
  }

  return -1;
}