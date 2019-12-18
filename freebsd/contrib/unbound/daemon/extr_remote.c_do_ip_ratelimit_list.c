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
struct TYPE_3__ {int /*<<< orphan*/ * now; TYPE_2__* infra_cache; } ;
struct worker {TYPE_1__ env; } ;
struct ip_ratelimit_list_arg {int all; TYPE_2__* infra; int /*<<< orphan*/ * ssl; int /*<<< orphan*/  now; } ;
struct TYPE_4__ {int /*<<< orphan*/ * client_ip_rates; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 scalar_t__ infra_ip_ratelimit ; 
 int /*<<< orphan*/  ip_rate_list ; 
 char* skipwhite (char*) ; 
 int /*<<< orphan*/  slabhash_traverse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ip_ratelimit_list_arg*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
do_ip_ratelimit_list(RES* ssl, struct worker* worker, char* arg)
{
	struct ip_ratelimit_list_arg a;
	a.all = 0;
	a.infra = worker->env.infra_cache;
	a.now = *worker->env.now;
	a.ssl = ssl;
	arg = skipwhite(arg);
	if(strcmp(arg, "+a") == 0)
		a.all = 1;
	if(a.infra->client_ip_rates==NULL ||
		(a.all == 0 && infra_ip_ratelimit == 0))
		return;
	slabhash_traverse(a.infra->client_ip_rates, 0, ip_rate_list, &a);
}