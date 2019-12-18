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
struct TYPE_2__ {scalar_t__ va_type; } ;
struct puffs_node {TYPE_1__ pn_va; } ;
struct dtfs_mount {int dtm_nfiles; } ;
struct dtfs_dirent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTFS_PTOF (struct puffs_node*) ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  assert (int) ; 
 struct dtfs_dirent* dtfs_dirgetbyname (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  dtfs_removedent (struct puffs_node*,struct dtfs_dirent*) ; 
 int /*<<< orphan*/  free (struct dtfs_dirent*) ; 
 struct dtfs_mount* puffs_pn_getmntspecific (struct puffs_node*) ; 

void
dtfs_nukenode(struct puffs_node *nukeme, struct puffs_node *pn_parent,
	const char *fname, size_t fnlen)
{
	struct dtfs_dirent *dfd;
	struct dtfs_mount *dtm;

	assert(pn_parent->pn_va.va_type == VDIR);

	dfd = dtfs_dirgetbyname(DTFS_PTOF(pn_parent), fname, fnlen);
	assert(dfd);

	dtm = puffs_pn_getmntspecific(nukeme);
	dtm->dtm_nfiles--;
	assert(dtm->dtm_nfiles >= 1);

	dtfs_removedent(pn_parent, dfd);
	free(dfd);
}