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
typedef  scalar_t__ u_int ;
struct inpcbinfo {scalar_t__ ipi_npcbgroups; struct inpcbgroup* ipi_pcbgroups; int /*<<< orphan*/  ipi_wildmask; void* ipi_wildbase; scalar_t__ ipi_hashfields; } ;
struct inpcbgroup {scalar_t__ ipg_cpu; int /*<<< orphan*/  ipg_hashmask; void* ipg_hashbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_GROUP_LOCK_INIT (struct inpcbgroup*,char*) ; 
 scalar_t__ IPI_HASHFIELDS_NONE ; 
 int /*<<< orphan*/  M_PCB ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 void* hashinit (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct inpcbgroup* malloc (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int mp_ncpus ; 
 scalar_t__ rss_getcpu (scalar_t__) ; 
 scalar_t__ rss_getnumbuckets () ; 

void
in_pcbgroup_init(struct inpcbinfo *pcbinfo, u_int hashfields,
    int hash_nelements)
{
	struct inpcbgroup *pcbgroup;
	u_int numpcbgroups, pgn;

	/*
	 * Only enable connection groups for a protocol if it has been
	 * specifically requested.
	 */
	if (hashfields == IPI_HASHFIELDS_NONE)
		return;

	/*
	 * Connection groups are about multi-processor load distribution,
	 * lock contention, and connection CPU affinity.  As such, no point
	 * in turning them on for a uniprocessor machine, it only wastes
	 * memory.
	 */
	if (mp_ncpus == 1)
		return;

#ifdef RSS
	/*
	 * If we're using RSS, then RSS determines the number of connection
	 * groups to use: one connection group per RSS bucket.  If for some
	 * reason RSS isn't able to provide a number of buckets, disable
	 * connection groups entirely.
	 *
	 * XXXRW: Can this ever happen?
	 */
	numpcbgroups = rss_getnumbuckets();
	if (numpcbgroups == 0)
		return;
#else
	/*
	 * Otherwise, we'll just use one per CPU for now.  If we decide to
	 * do dynamic rebalancing a la RSS, we'll need similar logic here.
	 */
	numpcbgroups = mp_ncpus;
#endif

	pcbinfo->ipi_hashfields = hashfields;
	pcbinfo->ipi_pcbgroups = malloc(numpcbgroups *
	    sizeof(*pcbinfo->ipi_pcbgroups), M_PCB, M_WAITOK | M_ZERO);
	pcbinfo->ipi_npcbgroups = numpcbgroups;
	pcbinfo->ipi_wildbase = hashinit(hash_nelements, M_PCB,
	    &pcbinfo->ipi_wildmask);
	for (pgn = 0; pgn < pcbinfo->ipi_npcbgroups; pgn++) {
		pcbgroup = &pcbinfo->ipi_pcbgroups[pgn];
		pcbgroup->ipg_hashbase = hashinit(hash_nelements, M_PCB,
		    &pcbgroup->ipg_hashmask);
		INP_GROUP_LOCK_INIT(pcbgroup, "pcbgroup");

		/*
		 * Initialise notional affinity of the pcbgroup -- for RSS,
		 * we want the same notion of affinity as NICs to be used.  In
		 * the non-RSS case, just round robin for the time being.
		 *
		 * XXXRW: The notion of a bucket to CPU mapping is common at
		 * both pcbgroup and RSS layers -- does that mean that we
		 * should migrate it all from RSS to here, and just leave RSS
		 * responsible only for providing hashing and mapping funtions?
		 */
#ifdef RSS
		pcbgroup->ipg_cpu = rss_getcpu(pgn);
#else
		pcbgroup->ipg_cpu = (pgn % mp_ncpus);
#endif
	}
}