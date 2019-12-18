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
typedef  scalar_t__ cl_t ;

/* Variables and functions */
 scalar_t__ CLUST_BAD ; 
 scalar_t__ CLUST_FREE ; 
 scalar_t__ CLUST_RSRVD ; 
 int FSERROR ; 
 int FSFATAL ; 
 int FSFATMOD ; 
 scalar_t__ ask (int,char*,...) ; 
 int /*<<< orphan*/  pwarn (char*,scalar_t__,scalar_t__,...) ; 
 scalar_t__ rsrvdcltype (scalar_t__) ; 

__attribute__((used)) static int
clustdiffer(cl_t cl, cl_t *cp1, cl_t *cp2, u_int fatnum)
{
	if (*cp1 == CLUST_FREE || *cp1 >= CLUST_RSRVD) {
		if (*cp2 == CLUST_FREE || *cp2 >= CLUST_RSRVD) {
			if ((*cp1 != CLUST_FREE && *cp1 < CLUST_BAD
			     && *cp2 != CLUST_FREE && *cp2 < CLUST_BAD)
			    || (*cp1 > CLUST_BAD && *cp2 > CLUST_BAD)) {
				pwarn("Cluster %u is marked %s with different indicators\n",
				      cl, rsrvdcltype(*cp1));
				if (ask(1, "Fix")) {
					*cp2 = *cp1;
					return FSFATMOD;
				}
				return FSFATAL;
			}
			pwarn("Cluster %u is marked %s in FAT 0, %s in FAT %u\n",
			      cl, rsrvdcltype(*cp1), rsrvdcltype(*cp2), fatnum);
			if (ask(0, "Use FAT 0's entry")) {
				*cp2 = *cp1;
				return FSFATMOD;
			}
			if (ask(0, "Use FAT %u's entry", fatnum)) {
				*cp1 = *cp2;
				return FSFATMOD;
			}
			return FSFATAL;
		}
		pwarn("Cluster %u is marked %s in FAT 0, but continues with cluster %u in FAT %d\n",
		      cl, rsrvdcltype(*cp1), *cp2, fatnum);
		if (ask(0, "Use continuation from FAT %u", fatnum)) {
			*cp1 = *cp2;
			return FSFATMOD;
		}
		if (ask(0, "Use mark from FAT 0")) {
			*cp2 = *cp1;
			return FSFATMOD;
		}
		return FSFATAL;
	}
	if (*cp2 == CLUST_FREE || *cp2 >= CLUST_RSRVD) {
		pwarn("Cluster %u continues with cluster %u in FAT 0, but is marked %s in FAT %u\n",
		      cl, *cp1, rsrvdcltype(*cp2), fatnum);
		if (ask(0, "Use continuation from FAT 0")) {
			*cp2 = *cp1;
			return FSFATMOD;
		}
		if (ask(0, "Use mark from FAT %d", fatnum)) {
			*cp1 = *cp2;
			return FSFATMOD;
		}
		return FSERROR;
	}
	pwarn("Cluster %u continues with cluster %u in FAT 0, but with cluster %u in FAT %u\n",
	      cl, *cp1, *cp2, fatnum);
	if (ask(0, "Use continuation from FAT 0")) {
		*cp2 = *cp1;
		return FSFATMOD;
	}
	if (ask(0, "Use continuation from FAT %u", fatnum)) {
		*cp1 = *cp2;
		return FSFATMOD;
	}
	return FSERROR;
}