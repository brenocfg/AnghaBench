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
struct vop_create_args {int /*<<< orphan*/ * a_vpp; int /*<<< orphan*/  a_dvp; int /*<<< orphan*/  a_vap; struct componentname* a_cnp; } ;
struct timespec {int dummy; } ;
struct denode {scalar_t__ de_StartCluster; scalar_t__ de_fndoffset; scalar_t__ de_FileSize; int de_flag; int /*<<< orphan*/  de_pmp; scalar_t__ de_LowerCase; int /*<<< orphan*/  de_Attributes; int /*<<< orphan*/  de_Name; } ;
struct componentname {int cn_flags; } ;
typedef  int /*<<< orphan*/  ndirent ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_ARCHIVE ; 
 int /*<<< orphan*/  DETIMES (struct denode*,struct timespec*,struct timespec*,struct timespec*) ; 
 int /*<<< orphan*/  DETOV (struct denode*) ; 
 int DE_ACCESS ; 
 int DE_CREATE ; 
 int DE_UPDATE ; 
 int ENOSPC ; 
 int HASBUF ; 
 int MAKEENTRY ; 
 scalar_t__ MSDOSFSROOT ; 
 struct denode* VTODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct componentname*) ; 
 int createde (struct denode*,struct denode*,struct denode**,struct componentname*) ; 
 int /*<<< orphan*/  memset (struct denode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,struct componentname*,int /*<<< orphan*/ ) ; 
 int uniqdosname (struct denode*,struct componentname*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_timestamp (struct timespec*) ; 

__attribute__((used)) static int
msdosfs_create(struct vop_create_args *ap)
{
	struct componentname *cnp = ap->a_cnp;
	struct denode ndirent;
	struct denode *dep;
	struct denode *pdep = VTODE(ap->a_dvp);
	struct timespec ts;
	int error;

#ifdef MSDOSFS_DEBUG
	printf("msdosfs_create(cnp %p, vap %p\n", cnp, ap->a_vap);
#endif

	/*
	 * If this is the root directory and there is no space left we
	 * can't do anything.  This is because the root directory can not
	 * change size.
	 */
	if (pdep->de_StartCluster == MSDOSFSROOT
	    && pdep->de_fndoffset >= pdep->de_FileSize) {
		error = ENOSPC;
		goto bad;
	}

	/*
	 * Create a directory entry for the file, then call createde() to
	 * have it installed. NOTE: DOS files are always executable.  We
	 * use the absence of the owner write bit to make the file
	 * readonly.
	 */
#ifdef DIAGNOSTIC
	if ((cnp->cn_flags & HASBUF) == 0)
		panic("msdosfs_create: no name");
#endif
	memset(&ndirent, 0, sizeof(ndirent));
	error = uniqdosname(pdep, cnp, ndirent.de_Name);
	if (error)
		goto bad;

	ndirent.de_Attributes = ATTR_ARCHIVE;
	ndirent.de_LowerCase = 0;
	ndirent.de_StartCluster = 0;
	ndirent.de_FileSize = 0;
	ndirent.de_pmp = pdep->de_pmp;
	ndirent.de_flag = DE_ACCESS | DE_CREATE | DE_UPDATE;
	vfs_timestamp(&ts);
	DETIMES(&ndirent, &ts, &ts, &ts);
	error = createde(&ndirent, pdep, &dep, cnp);
	if (error)
		goto bad;
	*ap->a_vpp = DETOV(dep);
	if ((cnp->cn_flags & MAKEENTRY) != 0)
		cache_enter(ap->a_dvp, *ap->a_vpp, cnp);
	return (0);

bad:
	return (error);
}