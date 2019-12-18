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
struct TYPE_2__ {struct config_file* cfg; } ;
struct worker {TYPE_1__ env; } ;
struct config_file {int /*<<< orphan*/  chrootdir; int /*<<< orphan*/  use_syslog; int /*<<< orphan*/  logfile; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  log_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_ok (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_log_reopen(RES* ssl, struct worker* worker)
{
	struct config_file* cfg = worker->env.cfg;
	send_ok(ssl);
	log_init(cfg->logfile, cfg->use_syslog, cfg->chrootdir);
}