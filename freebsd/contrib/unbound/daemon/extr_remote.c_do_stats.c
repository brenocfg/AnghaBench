#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  total ;
struct ub_stats_info {double mesh_time_median; } ;
struct daemon_remote {TYPE_2__* worker; } ;
struct daemon {int num; TYPE_1__* cfg; int /*<<< orphan*/ * workers; } ;
struct TYPE_6__ {struct daemon* daemon; } ;
struct TYPE_5__ {scalar_t__ stat_extended; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  memset (struct ub_stats_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_ext (int /*<<< orphan*/ *,struct ub_stats_info*) ; 
 int /*<<< orphan*/  print_hist (int /*<<< orphan*/ *,struct ub_stats_info*) ; 
 int /*<<< orphan*/  print_mem (int /*<<< orphan*/ *,TYPE_2__*,struct daemon*,struct ub_stats_info*) ; 
 int /*<<< orphan*/  print_stats (int /*<<< orphan*/ *,char*,struct ub_stats_info*) ; 
 int /*<<< orphan*/  print_thread_stats (int /*<<< orphan*/ *,int,struct ub_stats_info*) ; 
 int /*<<< orphan*/  print_uptime (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  server_stats_add (struct ub_stats_info*,struct ub_stats_info*) ; 
 int /*<<< orphan*/  server_stats_obtain (TYPE_2__*,int /*<<< orphan*/ ,struct ub_stats_info*,int) ; 

__attribute__((used)) static void
do_stats(RES* ssl, struct daemon_remote* rc, int reset)
{
	struct daemon* daemon = rc->worker->daemon;
	struct ub_stats_info total;
	struct ub_stats_info s;
	int i;
	memset(&total, 0, sizeof(total));
	log_assert(daemon->num > 0);
	/* gather all thread statistics in one place */
	for(i=0; i<daemon->num; i++) {
		server_stats_obtain(rc->worker, daemon->workers[i], &s, reset);
		if(!print_thread_stats(ssl, i, &s))
			return;
		if(i == 0)
			total = s;
		else	server_stats_add(&total, &s);
	}
	/* print the thread statistics */
	total.mesh_time_median /= (double)daemon->num;
	if(!print_stats(ssl, "total", &total)) 
		return;
	if(!print_uptime(ssl, rc->worker, reset))
		return;
	if(daemon->cfg->stat_extended) {
		if(!print_mem(ssl, rc->worker, daemon, &total)) 
			return;
		if(!print_hist(ssl, &total))
			return;
		if(!print_ext(ssl, &total))
			return;
	}
}