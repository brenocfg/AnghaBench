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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct nfscllayout {int nfsly_flags; int /*<<< orphan*/  nfsly_lock; scalar_t__ nfsly_timestamp; } ;
struct nfsclflayout {int dummy; } ;
struct nfsclclient {int /*<<< orphan*/  nfsc_layout; TYPE_1__* nfsc_nmp; } ;
typedef  int /*<<< orphan*/  mount_t ;
struct TYPE_2__ {int /*<<< orphan*/  nm_mountp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSCLSTATEMUTEXPTR ; 
 scalar_t__ NFSCL_FORCEDISM (int /*<<< orphan*/ ) ; 
 scalar_t__ NFSD_MONOSEC ; 
 int /*<<< orphan*/  NFSLOCKCLSTATE () ; 
 int NFSLY_RECALL ; 
 int /*<<< orphan*/  NFSUNLOCKCLSTATE () ; 
 int /*<<< orphan*/  NFSV4OPEN_ACCESSREAD ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct nfscllayout*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nfscllayout*,int /*<<< orphan*/ ) ; 
 struct nfscllayout* nfscl_findlayout (struct nfsclclient*,int /*<<< orphan*/ *,int) ; 
 int nfscl_findlayoutforio (struct nfscllayout*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsclflayout**) ; 
 int /*<<< orphan*/  nfsly_list ; 
 int /*<<< orphan*/  nfsv4_getref (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfsv4_lock (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct nfscllayout *
nfscl_getlayout(struct nfsclclient *clp, uint8_t *fhp, int fhlen,
    uint64_t off, struct nfsclflayout **retflpp, int *recalledp)
{
	struct nfscllayout *lyp;
	mount_t mp;
	int error, igotlock;

	mp = clp->nfsc_nmp->nm_mountp;
	*recalledp = 0;
	*retflpp = NULL;
	NFSLOCKCLSTATE();
	lyp = nfscl_findlayout(clp, fhp, fhlen);
	if (lyp != NULL) {
		if ((lyp->nfsly_flags & NFSLY_RECALL) == 0) {
			TAILQ_REMOVE(&clp->nfsc_layout, lyp, nfsly_list);
			TAILQ_INSERT_HEAD(&clp->nfsc_layout, lyp, nfsly_list);
			lyp->nfsly_timestamp = NFSD_MONOSEC + 120;
			error = nfscl_findlayoutforio(lyp, off,
			    NFSV4OPEN_ACCESSREAD, retflpp);
			if (error == 0)
				nfsv4_getref(&lyp->nfsly_lock, NULL,
				    NFSCLSTATEMUTEXPTR, mp);
			else {
				do {
					igotlock = nfsv4_lock(&lyp->nfsly_lock,
					    1, NULL, NFSCLSTATEMUTEXPTR, mp);
				} while (igotlock == 0 && !NFSCL_FORCEDISM(mp));
				*retflpp = NULL;
			}
			if (NFSCL_FORCEDISM(mp)) {
				lyp = NULL;
				*recalledp = 1;
			}
		} else {
			lyp = NULL;
			*recalledp = 1;
		}
	}
	NFSUNLOCKCLSTATE();
	return (lyp);
}