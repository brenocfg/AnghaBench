#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ipv6cp {int /*<<< orphan*/  throughput; } ;
struct fsm {TYPE_1__* link; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogIPV6CP ; 
 struct ipv6cp* fsm2ipv6cp (struct fsm*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throughput_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throughput_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ipv6cp_LayerFinish(struct fsm *fp)
{
  /* We're now down */
  struct ipv6cp *ipv6cp = fsm2ipv6cp(fp);

  log_Printf(LogIPV6CP, "%s: LayerFinish.\n", fp->link->name);
  throughput_stop(&ipv6cp->throughput);
  throughput_log(&ipv6cp->throughput, LogIPV6CP, NULL);
}