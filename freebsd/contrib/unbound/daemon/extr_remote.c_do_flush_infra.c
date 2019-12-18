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
struct TYPE_4__ {int* now; TYPE_1__* infra_cache; } ;
struct worker {TYPE_2__ env; } ;
struct sockaddr_storage {int dummy; } ;
struct del_info {int expired; int /*<<< orphan*/  addr; int /*<<< orphan*/  addrlen; scalar_t__ num_keys; scalar_t__ num_msgs; scalar_t__ num_rrsets; scalar_t__ labs; scalar_t__ len; scalar_t__ name; struct worker* worker; } ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_3__ {int /*<<< orphan*/  hosts; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  UNBOUND_DNS_PORT ; 
 int /*<<< orphan*/  infra_del_host ; 
 int /*<<< orphan*/  ipstrtoaddr (char*,int /*<<< orphan*/ ,struct sockaddr_storage*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_ok (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slabhash_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slabhash_traverse (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct del_info*) ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
do_flush_infra(RES* ssl, struct worker* worker, char* arg)
{
	struct sockaddr_storage addr;
	socklen_t len;
	struct del_info inf;
	if(strcmp(arg, "all") == 0) {
		slabhash_clear(worker->env.infra_cache->hosts);
		send_ok(ssl);
		return;
	}
	if(!ipstrtoaddr(arg, UNBOUND_DNS_PORT, &addr, &len)) {
		(void)ssl_printf(ssl, "error parsing ip addr: '%s'\n", arg);
		return;
	}
	/* delete all entries from cache */
	/* what we do is to set them all expired */
	inf.worker = worker;
	inf.name = 0;
	inf.len = 0;
	inf.labs = 0;
	inf.expired = *worker->env.now;
	inf.expired -= 3; /* handle 3 seconds skew between threads */
	inf.num_rrsets = 0;
	inf.num_msgs = 0;
	inf.num_keys = 0;
	inf.addrlen = len;
	memmove(&inf.addr, &addr, len);
	slabhash_traverse(worker->env.infra_cache->hosts, 1, &infra_del_host,
		&inf);
	send_ok(ssl);
}