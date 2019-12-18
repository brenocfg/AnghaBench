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
struct sockaddr {int sa_family; } ;
struct radix_node_head {int /*<<< orphan*/  rh; scalar_t__ (* rnh_matchaddr ) (struct sockaddr*,int /*<<< orphan*/ *) ;} ;
struct netcred {TYPE_1__* netc_rnodes; } ;
struct netexport {struct netcred ne_defexported; struct radix_node_head* ne6; struct radix_node_head* ne4; } ;
struct mount {int mnt_flag; struct netexport* mnt_export; } ;
struct TYPE_2__ {int rn_flags; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int MNT_DEFEXPORTED ; 
 int MNT_EXPORTED ; 
 int /*<<< orphan*/  RADIX_NODE_HEAD_RLOCK (struct radix_node_head*) ; 
 int /*<<< orphan*/  RADIX_NODE_HEAD_RLOCK_TRACKER ; 
 int /*<<< orphan*/  RADIX_NODE_HEAD_RUNLOCK (struct radix_node_head*) ; 
 int RNF_ROOT ; 
 scalar_t__ stub1 (struct sockaddr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct netcred *
vfs_export_lookup(struct mount *mp, struct sockaddr *nam)
{
	RADIX_NODE_HEAD_RLOCK_TRACKER;
	struct netexport *nep;
	struct netcred *np = NULL;
	struct radix_node_head *rnh;
	struct sockaddr *saddr;

	nep = mp->mnt_export;
	if (nep == NULL)
		return (NULL);
	if ((mp->mnt_flag & MNT_EXPORTED) == 0)
		return (NULL);

	/*
	 * Lookup in the export list
	 */
	if (nam != NULL) {
		saddr = nam;
		rnh = NULL;
		switch (saddr->sa_family) {
		case AF_INET:
			rnh = nep->ne4;
			break;
		case AF_INET6:
			rnh = nep->ne6;
			break;
		}
		if (rnh != NULL) {
			RADIX_NODE_HEAD_RLOCK(rnh);
			np = (struct netcred *) (*rnh->rnh_matchaddr)(saddr, &rnh->rh);
			RADIX_NODE_HEAD_RUNLOCK(rnh);
			if (np != NULL && (np->netc_rnodes->rn_flags & RNF_ROOT) != 0)
				return (NULL);
		}
	}

	/*
	 * If no address match, use the default if it exists.
	 */
	if (np == NULL && (mp->mnt_flag & MNT_DEFEXPORTED) != 0)
		return (&nep->ne_defexported);

	return (np);
}