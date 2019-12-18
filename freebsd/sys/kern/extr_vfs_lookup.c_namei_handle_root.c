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
struct vnode {int dummy; } ;
struct componentname {int cn_flags; char* cn_nameptr; } ;
struct nameidata {int ni_lcf; struct vnode* ni_rootdir; int /*<<< orphan*/  ni_pathlen; struct componentname ni_cnd; } ;

/* Variables and functions */
 int BENEATH ; 
 int /*<<< orphan*/  CAPFAIL_LOOKUP ; 
 int ENOTCAPABLE ; 
 scalar_t__ KTRPOINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_CAPFAIL ; 
 int NI_LCF_BENEATH_ABS ; 
 int NI_LCF_BENEATH_LATCHED ; 
 int NI_LCF_STRICTRELATIVE ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  ktrcapfail (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nameicap_cleanup (struct nameidata*,int) ; 
 int /*<<< orphan*/  vrefact (struct vnode*) ; 

__attribute__((used)) static int
namei_handle_root(struct nameidata *ndp, struct vnode **dpp)
{
	struct componentname *cnp;

	cnp = &ndp->ni_cnd;
	if ((ndp->ni_lcf & NI_LCF_STRICTRELATIVE) != 0) {
#ifdef KTRACE
		if (KTRPOINT(curthread, KTR_CAPFAIL))
			ktrcapfail(CAPFAIL_LOOKUP, NULL, NULL);
#endif
		return (ENOTCAPABLE);
	}
	if ((cnp->cn_flags & BENEATH) != 0) {
		ndp->ni_lcf |= NI_LCF_BENEATH_ABS;
		ndp->ni_lcf &= ~NI_LCF_BENEATH_LATCHED;
		nameicap_cleanup(ndp, false);
	}
	while (*(cnp->cn_nameptr) == '/') {
		cnp->cn_nameptr++;
		ndp->ni_pathlen--;
	}
	*dpp = ndp->ni_rootdir;
	vrefact(*dpp);
	return (0);
}