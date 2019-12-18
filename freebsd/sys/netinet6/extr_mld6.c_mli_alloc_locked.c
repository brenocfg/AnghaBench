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
struct mld_ifsoftc {int /*<<< orphan*/  mli_gq; int /*<<< orphan*/  mli_uri; int /*<<< orphan*/  mli_qri; int /*<<< orphan*/  mli_qi; int /*<<< orphan*/  mli_rv; scalar_t__ mli_flags; int /*<<< orphan*/  mli_version; struct ifnet* mli_ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_MLD ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct mld_ifsoftc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLD_LOCK_ASSERT () ; 
 int /*<<< orphan*/  MLD_MAX_RESPONSE_PACKETS ; 
 int /*<<< orphan*/  MLD_QI_INIT ; 
 int /*<<< orphan*/  MLD_QRI_INIT ; 
 int /*<<< orphan*/  MLD_RV_INIT ; 
 int /*<<< orphan*/  MLD_URI_INIT ; 
 int /*<<< orphan*/  MLD_VERSION_2 ; 
 int /*<<< orphan*/  M_MLD ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  V_mli_head ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 struct mld_ifsoftc* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mbufq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mli_link ; 

__attribute__((used)) static struct mld_ifsoftc *
mli_alloc_locked(/*const*/ struct ifnet *ifp)
{
	struct mld_ifsoftc *mli;

	MLD_LOCK_ASSERT();

	mli = malloc(sizeof(struct mld_ifsoftc), M_MLD, M_NOWAIT|M_ZERO);
	if (mli == NULL)
		goto out;

	mli->mli_ifp = ifp;
	mli->mli_version = MLD_VERSION_2;
	mli->mli_flags = 0;
	mli->mli_rv = MLD_RV_INIT;
	mli->mli_qi = MLD_QI_INIT;
	mli->mli_qri = MLD_QRI_INIT;
	mli->mli_uri = MLD_URI_INIT;
	mbufq_init(&mli->mli_gq, MLD_MAX_RESPONSE_PACKETS);

	LIST_INSERT_HEAD(&V_mli_head, mli, mli_link);

	CTR2(KTR_MLD, "allocate mld_ifsoftc for ifp %p(%s)",
	     ifp, if_name(ifp));

out:
	return (mli);
}