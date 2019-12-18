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
typedef  int /*<<< orphan*/  u_int ;
struct bootblock {int ClustMask; int NumClusters; int /*<<< orphan*/  NumBad; int /*<<< orphan*/  NumFree; } ;
typedef  int cl_t ;

/* Variables and functions */
 int CLUST_BAD ; 
 int CLUST_EOF ; 
 int CLUST_EOFS ; 
 int CLUST_FIRST ; 
 int CLUST_FREE ; 
 int CLUST_RSRVD ; 
 int FSERROR ; 
 int FSFATMOD ; 
 int FSOK ; 
 scalar_t__ ask (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pwarn (char*,int,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
checkclnum(struct bootblock *boot, u_int fat, cl_t cl, cl_t *next)
{
	if (*next >= (CLUST_RSRVD&boot->ClustMask))
		*next |= ~boot->ClustMask;
	if (*next == CLUST_FREE) {
		boot->NumFree++;
		return FSOK;
	}
	if (*next == CLUST_BAD) {
		boot->NumBad++;
		return FSOK;
	}
	if (*next < CLUST_FIRST
	    || (*next >= boot->NumClusters && *next < CLUST_EOFS)) {
		pwarn("Cluster %u in FAT %d continues with %s cluster number %u\n",
		      cl, fat,
		      *next < CLUST_RSRVD ? "out of range" : "reserved",
		      *next&boot->ClustMask);
		if (ask(0, "Truncate")) {
			*next = CLUST_EOF;
			return FSFATMOD;
		}
		return FSERROR;
	}
	return FSOK;
}