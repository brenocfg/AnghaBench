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
struct TYPE_6__ {int maxreq; } ;
struct TYPE_7__ {TYPE_2__ fsm; } ;
struct ipv6cp {scalar_t__ peer_tokenreq; TYPE_3__ cfg; int /*<<< orphan*/  throughput; } ;
struct TYPE_5__ {int reqs; int naks; int rejs; } ;
struct fsm {TYPE_1__ more; int /*<<< orphan*/  bundle; TYPE_4__* link; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  Enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogIPV6CP ; 
 int /*<<< orphan*/  OPT_THROUGHPUT ; 
 struct ipv6cp* fsm2ipv6cp (struct fsm*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throughput_start (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipv6cp_LayerStart(struct fsm *fp)
{
  /* We're about to start up ! */
  struct ipv6cp *ipv6cp = fsm2ipv6cp(fp);

  log_Printf(LogIPV6CP, "%s: LayerStart.\n", fp->link->name);
  throughput_start(&ipv6cp->throughput, "IPV6CP throughput",
                   Enabled(fp->bundle, OPT_THROUGHPUT));
  fp->more.reqs = fp->more.naks = fp->more.rejs = ipv6cp->cfg.fsm.maxreq * 3;
  ipv6cp->peer_tokenreq = 0;
}