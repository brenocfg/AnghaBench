#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hifn_stats {int hst_invalid; int hst_nomem; int hst_abort; int hst_noirq; int hst_unaligned; int hst_totbatch; int hst_maxbatch; int hst_nomem_map; int hst_nomem_load; int hst_nomem_mbuf; int hst_nomem_mcl; int hst_nomem_cr; int hst_nomem_sd; int /*<<< orphan*/  hst_opackets; int /*<<< orphan*/  hst_obytes; int /*<<< orphan*/  hst_ipackets; int /*<<< orphan*/  hst_ibytes; } ;
typedef  int /*<<< orphan*/  stats ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 
 scalar_t__ sysctlbyname (char*,struct hifn_stats*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	struct hifn_stats stats;
	size_t slen;

	slen = sizeof (stats);
	if (sysctlbyname("hw.hifn.stats", &stats, &slen, NULL, 0) < 0)
		err(1, "kern.hifn.stats");

	printf("input %llu bytes %u packets\n",
		stats.hst_ibytes, stats.hst_ipackets);
	printf("output %llu bytes %u packets\n",
		stats.hst_obytes, stats.hst_opackets);
	printf("invalid %u nomem %u abort %u\n",
		stats.hst_invalid, stats.hst_nomem, stats.hst_abort);
	printf("noirq %u unaligned %u\n",
		stats.hst_noirq, stats.hst_unaligned);
	printf("totbatch %u maxbatch %u\n",
		stats.hst_totbatch, stats.hst_maxbatch);
	printf("nomem: map %u load %u mbuf %u mcl %u cr %u sd %u\n",
		stats.hst_nomem_map, stats.hst_nomem_load,
		stats.hst_nomem_mbuf, stats.hst_nomem_mcl,
		stats.hst_nomem_cr, stats.hst_nomem_sd);
	return 0;
}