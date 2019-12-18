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
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int BXE_L2_MAX_CID (struct bxe_softc*) ; 
 scalar_t__ BXE_VF_CIDS ; 
 scalar_t__ CNIC_CID_MAX ; 
 scalar_t__ CNIC_SUPPORT (struct bxe_softc*) ; 
 scalar_t__ IS_SRIOV (struct bxe_softc*) ; 
 int /*<<< orphan*/  QM_CID_ROUND ; 
 int roundup (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bxe_set_qm_cid_count(struct bxe_softc *sc)
{
    int cid_count = BXE_L2_MAX_CID(sc);

    if (IS_SRIOV(sc)) {
        cid_count += BXE_VF_CIDS;
    }

    if (CNIC_SUPPORT(sc)) {
        cid_count += CNIC_CID_MAX;
    }

    return (roundup(cid_count, QM_CID_ROUND));
}