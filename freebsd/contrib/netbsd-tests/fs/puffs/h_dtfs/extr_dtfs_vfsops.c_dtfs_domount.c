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
struct puffs_usermount {int dummy; } ;
struct puffs_node {int dummy; } ;
struct dtfs_mount {int dtm_nextfileid; int dtm_nfiles; int /*<<< orphan*/  dtm_pollent; scalar_t__ dtm_fsizes; } ;
struct dtfs_file {int /*<<< orphan*/ * df_dotdot; } ;
struct TYPE_2__ {scalar_t__ (* pfunc ) (struct puffs_usermount*,char const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  vt; int /*<<< orphan*/  tstr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int NTYPES ; 
 int /*<<< orphan*/  VDIR ; 
 struct dtfs_file* dtfs_newdir () ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 struct dtfs_mount* puffs_getspecific (struct puffs_usermount*) ; 
 struct puffs_node* puffs_pn_new (struct puffs_usermount*,struct dtfs_file*) ; 
 int /*<<< orphan*/  puffs_setroot (struct puffs_usermount*,struct puffs_node*) ; 
 int /*<<< orphan*/  rtnorm (struct puffs_usermount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* rtypes ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct puffs_usermount*,char const*,int /*<<< orphan*/ ) ; 

int
dtfs_domount(struct puffs_usermount *pu, const char *typestr)
{
	struct dtfs_mount *dtm;
	struct dtfs_file *dff;
	struct puffs_node *pn;
	int i;

	/* create mount-local thingie */
	dtm = puffs_getspecific(pu);
	dtm->dtm_nextfileid = 3;
	dtm->dtm_nfiles = 1;
	dtm->dtm_fsizes = 0;
	LIST_INIT(&dtm->dtm_pollent);

	/*
	 * create root directory, do it "by hand" to avoid special-casing
	 * dtfs_genfile()
	 */
	dff = dtfs_newdir();
	dff->df_dotdot = NULL;
	pn = puffs_pn_new(pu, dff);
	if (!pn)
		errx(1, "puffs_newpnode");
	puffs_setroot(pu, pn);

	if (!typestr) {
		rtnorm(pu, NULL, VDIR);
	} else {
		for (i = 0; i < NTYPES; i++) {
			if (strncmp(rtypes[i].tstr, typestr,
			    strlen(rtypes[i].tstr)) == 0) {
				if (rtypes[i].pfunc(pu, typestr,
				    rtypes[i].vt) != 0) {
					fprintf(stderr, "failed to parse "
					    "\"%s\"\n", typestr);
					return 1;
				}
				break;
			}
		}
		if (i == NTYPES) {
			fprintf(stderr, "no maching type for %s\n", typestr);
			return 1;
		}
	}

	return 0;
}