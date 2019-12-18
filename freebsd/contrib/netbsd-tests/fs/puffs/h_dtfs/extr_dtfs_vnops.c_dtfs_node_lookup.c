#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct puffs_usermount {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  va_gid; int /*<<< orphan*/  va_uid; int /*<<< orphan*/  va_mode; } ;
struct puffs_node {TYPE_2__ pn_va; } ;
struct puffs_newinfo {int dummy; } ;
struct puffs_cn {int pcn_flags; scalar_t__ pcn_nameiop; int /*<<< orphan*/  pcn_cred; int /*<<< orphan*/  pcn_namelen; int /*<<< orphan*/  pcn_name; } ;
struct dtfs_file {TYPE_3__* df_dotdot; } ;
struct dtfs_dirent {TYPE_3__* dfd_node; } ;
struct TYPE_5__ {scalar_t__ va_type; int /*<<< orphan*/  va_rdev; int /*<<< orphan*/  va_size; } ;
struct TYPE_7__ {TYPE_1__ pn_va; } ;

/* Variables and functions */
 struct dtfs_file* DTFS_CTOF (void*) ; 
 int ENOENT ; 
 scalar_t__ NAMEI_CREATE ; 
 scalar_t__ NAMEI_DELETE ; 
 int NAMEI_ISLASTCN ; 
 scalar_t__ NAMEI_RENAME ; 
 scalar_t__ PCNISDOTDOT (struct puffs_cn const*) ; 
 int /*<<< orphan*/  PUFFS_VWRITE ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  assert (int) ; 
 struct dtfs_dirent* dtfs_dirgetbyname (struct dtfs_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int puffs_access (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puffs_flush_pagecache_node (struct puffs_usermount*,TYPE_3__*) ; 
 int /*<<< orphan*/  puffs_newinfo_setcookie (struct puffs_newinfo*,TYPE_3__*) ; 
 int /*<<< orphan*/  puffs_newinfo_setrdev (struct puffs_newinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puffs_newinfo_setsize (struct puffs_newinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puffs_newinfo_setvtype (struct puffs_newinfo*,scalar_t__) ; 

int
dtfs_node_lookup(struct puffs_usermount *pu, void *opc,
	struct puffs_newinfo *pni, const struct puffs_cn *pcn)
{
	struct puffs_node *pn_dir = opc;
	struct dtfs_file *df = DTFS_CTOF(opc);
	struct dtfs_dirent *dfd;
	extern int straightflush;
	int rv;

	/* parent dir? */
	if (PCNISDOTDOT(pcn)) {
		if (df->df_dotdot == NULL)
			return ENOENT;

		assert(df->df_dotdot->pn_va.va_type == VDIR);
		puffs_newinfo_setcookie(pni, df->df_dotdot);
		puffs_newinfo_setvtype(pni, df->df_dotdot->pn_va.va_type);

		return 0;
	}

	dfd = dtfs_dirgetbyname(df, pcn->pcn_name, pcn->pcn_namelen);
	if (dfd) {
		if ((pcn->pcn_flags & NAMEI_ISLASTCN) &&
		    (pcn->pcn_nameiop == NAMEI_DELETE)) {
			rv = puffs_access(VDIR, pn_dir->pn_va.va_mode,
			    pn_dir->pn_va.va_uid, pn_dir->pn_va.va_gid,
			    PUFFS_VWRITE, pcn->pcn_cred);
			if (rv)
				return rv;
		}
		puffs_newinfo_setcookie(pni, dfd->dfd_node);
		puffs_newinfo_setvtype(pni, dfd->dfd_node->pn_va.va_type);
		puffs_newinfo_setsize(pni, dfd->dfd_node->pn_va.va_size);
		puffs_newinfo_setrdev(pni, dfd->dfd_node->pn_va.va_rdev);

		if (straightflush)
			puffs_flush_pagecache_node(pu, dfd->dfd_node);

		return 0;
	}

	if ((pcn->pcn_flags & NAMEI_ISLASTCN)
	    && (pcn->pcn_nameiop == NAMEI_CREATE ||
	        pcn->pcn_nameiop == NAMEI_RENAME)) {
		rv = puffs_access(VDIR, pn_dir->pn_va.va_mode,
		    pn_dir->pn_va.va_uid, pn_dir->pn_va.va_gid,
		    PUFFS_VWRITE, pcn->pcn_cred);
		if (rv)
			return rv;
	}

	return ENOENT;
}