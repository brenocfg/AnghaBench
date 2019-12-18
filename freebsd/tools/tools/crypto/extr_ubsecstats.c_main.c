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
struct ubsec_stats {int hst_invalid; int hst_badsession; int hst_badflags; int hst_nodesc; int hst_badalg; int hst_nomem; int hst_queuefull; int hst_dmaerr; int hst_mcrerr; int hst_nodmafree; int hst_lenmismatch; int hst_skipmismatch; int hst_iovmisaligned; int hst_noirq; int hst_unaligned; int hst_nomap; int hst_noload; int hst_nomcl; int hst_totbatch; int hst_maxbatch; int hst_maxqueue; int hst_maxqchip; int hst_mcr1full; int hst_rng; int hst_modexp; int hst_modexpcrt; int /*<<< orphan*/  hst_opackets; int /*<<< orphan*/  hst_obytes; int /*<<< orphan*/  hst_ipackets; int /*<<< orphan*/  hst_ibytes; } ;
typedef  int /*<<< orphan*/  stats ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 
 scalar_t__ sysctlbyname (char*,struct ubsec_stats*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	struct ubsec_stats stats;
	size_t slen;

	slen = sizeof (stats);
	if (sysctlbyname("hw.ubsec.stats", &stats, &slen, NULL, 0) < 0)
		err(1, "kern.ubsec_stats");

	printf("input %llu bytes %u packets\n",
		stats.hst_ibytes, stats.hst_ipackets);
	printf("output %llu bytes %u packets\n",
		stats.hst_obytes, stats.hst_opackets);
	printf("invalid %u badsession %u badflags %u\n",
		stats.hst_invalid, stats.hst_badsession, stats.hst_badflags);
	printf("nodesc %u badalg %u nomem %u queuefull %u\n",
		stats.hst_nodesc, stats.hst_badalg, stats.hst_nomem,
		stats.hst_queuefull);
	printf("dmaerr %u mcrerr %u nodmafree %u\n",
		stats.hst_dmaerr, stats.hst_mcrerr, stats.hst_nodmafree);
	printf("lenmismatch %u skipmisatch %u iovmisalined %u\n",
		stats.hst_lenmismatch, stats.hst_skipmismatch,
		stats.hst_iovmisaligned);
	printf("noirq %u unaligned %u nomap %u noload %u nomcl %u\n",
		stats.hst_noirq, stats.hst_unaligned, stats.hst_nomap,
		stats.hst_noload, stats.hst_nomcl);
	printf("totbatch %u maxbatch %u\n",
		stats.hst_totbatch, stats.hst_maxbatch);
	printf("maxqueue %u maxqchip %u mcr1full %u\n",
		stats.hst_maxqueue, stats.hst_maxqchip, stats.hst_mcr1full);
	printf("rng %u modexp %u moexpcrt %u\n",
		stats.hst_rng, stats.hst_modexp, stats.hst_modexpcrt);
	return 0;
}