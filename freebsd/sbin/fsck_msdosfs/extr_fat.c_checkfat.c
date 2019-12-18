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
struct fatEntry {size_t head; size_t next; scalar_t__ length; } ;
struct bootblock {size_t NumClusters; } ;
typedef  size_t cl_t ;

/* Variables and functions */
 size_t CLUST_BAD ; 
 size_t CLUST_EOFS ; 
 size_t CLUST_FIRST ; 
 size_t CLUST_FREE ; 
 size_t CLUST_RSRVD ; 
 int FSERROR ; 
 int FSFATMOD ; 
 scalar_t__ ask (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  clearchain (struct bootblock*,struct fatEntry*,size_t) ; 
 int /*<<< orphan*/  pwarn (char*,size_t,size_t,...) ; 
 int /*<<< orphan*/  rsrvdcltype (size_t) ; 
 int tryclear (struct bootblock*,struct fatEntry*,size_t,size_t*) ; 

int
checkfat(struct bootblock *boot, struct fatEntry *fat)
{
	cl_t head, p, h, n;
	u_int len;
	int ret = 0;
	int conf;

	/*
	 * pass 1: figure out the cluster chains.
	 */
	for (head = CLUST_FIRST; head < boot->NumClusters; head++) {
		/* find next untravelled chain */
		if (fat[head].head != 0		/* cluster already belongs to some chain */
		    || fat[head].next == CLUST_FREE
		    || fat[head].next == CLUST_BAD)
			continue;		/* skip it. */

		/* follow the chain and mark all clusters on the way */
		for (len = 0, p = head;
		     p >= CLUST_FIRST && p < boot->NumClusters &&
		     fat[p].head != head;
		     p = fat[p].next) {
			fat[p].head = head;
			len++;
		}

		/* the head record gets the length */
		fat[head].length = fat[head].next == CLUST_FREE ? 0 : len;
	}

	/*
	 * pass 2: check for crosslinked chains (we couldn't do this in pass 1 because
	 * we didn't know the real start of the chain then - would have treated partial
	 * chains as interlinked with their main chain)
	 */
	for (head = CLUST_FIRST; head < boot->NumClusters; head++) {
		/* find next untravelled chain */
		if (fat[head].head != head)
			continue;

		/* follow the chain to its end (hopefully) */
		for (len = fat[head].length, p = head;
		     (n = fat[p].next) >= CLUST_FIRST && n < boot->NumClusters;
		     p = n)
			if (fat[n].head != head || len-- < 2)
				break;
		if (n >= CLUST_EOFS)
			continue;

		if (n == CLUST_FREE || n >= CLUST_RSRVD) {
			pwarn("Cluster chain starting at %u ends with cluster marked %s\n",
			      head, rsrvdcltype(n));
clear:
			ret |= tryclear(boot, fat, head, &fat[p].next);
			continue;
		}
		if (n < CLUST_FIRST || n >= boot->NumClusters) {
			pwarn("Cluster chain starting at %u ends with cluster out of range (%u)\n",
			    head, n);
			goto clear;
		}
		if (head == fat[n].head) {
			pwarn("Cluster chain starting at %u loops at cluster %u\n",
			    head, p);
			goto clear;
		}
		pwarn("Cluster chains starting at %u and %u are linked at cluster %u\n",
		      head, fat[n].head, n);
		conf = tryclear(boot, fat, head, &fat[p].next);
		if (ask(0, "Clear chain starting at %u", h = fat[n].head)) {
			if (conf == FSERROR) {
				/*
				 * Transfer the common chain to the one not cleared above.
				 */
				for (p = n;
				     p >= CLUST_FIRST && p < boot->NumClusters;
				     p = fat[p].next) {
					if (h != fat[p].head) {
						/*
						 * Have to reexamine this chain.
						 */
						head--;
						break;
					}
					fat[p].head = head;
				}
			}
			clearchain(boot, fat, h);
			conf |= FSFATMOD;
		}
		ret |= conf;
	}

	return ret;
}