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
struct infra_arg {TYPE_2__* infra; scalar_t__ ssl_failed; int /*<<< orphan*/  now; int /*<<< orphan*/ * ssl; } ;
struct TYPE_4__ {int /*<<< orphan*/  hosts; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  dump_infra_host ; 
 int /*<<< orphan*/  slabhash_traverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void
do_dump_infra(RES* ssl, struct worker* worker)
{
	struct infra_arg arg;
	arg.infra = worker->env.infra_cache;
	arg.ssl = ssl;
	arg.now = *worker->env.now;
	arg.ssl_failed = 0;
	slabhash_traverse(arg.infra->hosts, 0, &dump_infra_host, (void*)&arg);
}