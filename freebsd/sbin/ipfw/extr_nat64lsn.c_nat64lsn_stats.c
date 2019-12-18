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
typedef  char const* uintmax_t ;
typedef  scalar_t__ uint8_t ;
struct ipfw_nat64lsn_stats {scalar_t__ sdeleted; scalar_t__ screated; scalar_t__ icmpchunks; scalar_t__ udpchunks; scalar_t__ tcpchunks; scalar_t__ jportfails; scalar_t__ spgdeleted; scalar_t__ spgcreated; scalar_t__ jportreq; scalar_t__ jhostfails; scalar_t__ jhostsreq; scalar_t__ hostcount; scalar_t__ jnomem; scalar_t__ jmaxlen; scalar_t__ jrequests; scalar_t__ jcalls; scalar_t__ jreinjected; scalar_t__ nomatch4; scalar_t__ dropped; scalar_t__ nomem; scalar_t__ noproto; scalar_t__ noroute6; scalar_t__ noroute4; scalar_t__ oerrors; scalar_t__ ifrags; scalar_t__ ofrags; scalar_t__ opcnt46; scalar_t__ opcnt64; } ;
struct TYPE_2__ {scalar_t__ use_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 TYPE_1__ co ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nat64lsn_get_stats (char const*,scalar_t__,struct ipfw_nat64lsn_stats*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static void
nat64lsn_stats(const char *name, uint8_t set)
{
	struct ipfw_nat64lsn_stats stats;

	if (nat64lsn_get_stats(name, set, &stats) != 0)
		err(EX_OSERR, "Error retrieving stats");

	if (co.use_set != 0 || set != 0)
		printf("set %u ", set);
	printf("nat64lsn %s\n", name);
	printf("\t%ju packets translated from IPv6 to IPv4\n",
	    (uintmax_t)stats.opcnt64);
	printf("\t%ju packets translated from IPv4 to IPv6\n",
	    (uintmax_t)stats.opcnt46);
	printf("\t%ju IPv6 fragments created\n",
	    (uintmax_t)stats.ofrags);
	printf("\t%ju IPv4 fragments received\n",
	    (uintmax_t)stats.ifrags);
	printf("\t%ju output packets dropped due to no bufs, etc.\n",
	    (uintmax_t)stats.oerrors);
	printf("\t%ju output packets discarded due to no IPv4 route\n",
	    (uintmax_t)stats.noroute4);
	printf("\t%ju output packets discarded due to no IPv6 route\n",
	    (uintmax_t)stats.noroute6);
	printf("\t%ju packets discarded due to unsupported protocol\n",
	    (uintmax_t)stats.noproto);
	printf("\t%ju packets discarded due to memory allocation problems\n",
	    (uintmax_t)stats.nomem);
	printf("\t%ju packets discarded due to some errors\n",
	    (uintmax_t)stats.dropped);
	printf("\t%ju packets not matched with IPv4 prefix\n",
	    (uintmax_t)stats.nomatch4);

	printf("\t%ju mbufs queued for post processing\n",
	    (uintmax_t)stats.jreinjected);
	printf("\t%ju times the job queue was processed\n",
	    (uintmax_t)stats.jcalls);
	printf("\t%ju job requests queued\n",
	    (uintmax_t)stats.jrequests);
	printf("\t%ju job requests queue limit reached\n",
	    (uintmax_t)stats.jmaxlen);
	printf("\t%ju job requests failed due to memory allocation problems\n",
	    (uintmax_t)stats.jnomem);

	printf("\t%ju hosts allocated\n", (uintmax_t)stats.hostcount);
	printf("\t%ju hosts requested\n", (uintmax_t)stats.jhostsreq);
	printf("\t%ju host requests failed\n", (uintmax_t)stats.jhostfails);

	printf("\t%ju portgroups requested\n", (uintmax_t)stats.jportreq);
	printf("\t%ju portgroups allocated\n", (uintmax_t)stats.spgcreated);
	printf("\t%ju portgroups deleted\n", (uintmax_t)stats.spgdeleted);
	printf("\t%ju portgroup requests failed\n",
	    (uintmax_t)stats.jportfails);
	printf("\t%ju portgroups allocated for TCP\n",
	    (uintmax_t)stats.tcpchunks);
	printf("\t%ju portgroups allocated for UDP\n",
	    (uintmax_t)stats.udpchunks);
	printf("\t%ju portgroups allocated for ICMP\n",
	    (uintmax_t)stats.icmpchunks);

	printf("\t%ju states created\n", (uintmax_t)stats.screated);
	printf("\t%ju states deleted\n", (uintmax_t)stats.sdeleted);
}