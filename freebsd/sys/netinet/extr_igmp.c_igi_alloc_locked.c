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
struct igmp_ifsoftc {int /*<<< orphan*/  igi_gq; int /*<<< orphan*/  igi_uri; int /*<<< orphan*/  igi_qri; int /*<<< orphan*/  igi_qi; int /*<<< orphan*/  igi_rv; scalar_t__ igi_flags; int /*<<< orphan*/  igi_version; struct ifnet* igi_ifp; } ;
struct ifnet {int /*<<< orphan*/  if_xname; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IGMP_LOCK_ASSERT () ; 
 int /*<<< orphan*/  IGMP_MAX_RESPONSE_PACKETS ; 
 int /*<<< orphan*/  IGMP_QI_INIT ; 
 int /*<<< orphan*/  IGMP_QRI_INIT ; 
 int /*<<< orphan*/  IGMP_RV_INIT ; 
 int /*<<< orphan*/  IGMP_URI_INIT ; 
 int /*<<< orphan*/  KTR_IGMPV3 ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct igmp_ifsoftc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IGMP ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  V_igi_head ; 
 int /*<<< orphan*/  V_igmp_default_version ; 
 int /*<<< orphan*/  igi_link ; 
 struct igmp_ifsoftc* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mbufq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct igmp_ifsoftc *
igi_alloc_locked(/*const*/ struct ifnet *ifp)
{
	struct igmp_ifsoftc *igi;

	IGMP_LOCK_ASSERT();

	igi = malloc(sizeof(struct igmp_ifsoftc), M_IGMP, M_NOWAIT|M_ZERO);
	if (igi == NULL)
		goto out;

	igi->igi_ifp = ifp;
	igi->igi_version = V_igmp_default_version;
	igi->igi_flags = 0;
	igi->igi_rv = IGMP_RV_INIT;
	igi->igi_qi = IGMP_QI_INIT;
	igi->igi_qri = IGMP_QRI_INIT;
	igi->igi_uri = IGMP_URI_INIT;
	mbufq_init(&igi->igi_gq, IGMP_MAX_RESPONSE_PACKETS);

	LIST_INSERT_HEAD(&V_igi_head, igi, igi_link);

	CTR2(KTR_IGMPV3, "allocate igmp_ifsoftc for ifp %p(%s)",
	     ifp, ifp->if_xname);

out:
	return (igi);
}