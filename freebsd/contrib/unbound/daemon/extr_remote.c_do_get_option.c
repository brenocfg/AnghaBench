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
struct TYPE_2__ {int /*<<< orphan*/  cfg; } ;
struct worker {TYPE_1__ env; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int config_get_option (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remote_get_opt_ssl ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
do_get_option(RES* ssl, struct worker* worker, char* arg)
{
	int r;
	r = config_get_option(worker->env.cfg, arg, remote_get_opt_ssl, ssl);
	if(!r) {
		(void)ssl_printf(ssl, "error unknown option\n");
		return;
	}
}