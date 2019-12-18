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
typedef  scalar_t__ uint8_t ;
struct bxe_softc {int /*<<< orphan*/  ifp; } ;
struct bxe_fastpath {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_Q_FLG_LEADING_RSS ; 
 int /*<<< orphan*/  ECORE_Q_FLG_MCAST ; 
 int /*<<< orphan*/  ECORE_Q_FLG_OV ; 
 int /*<<< orphan*/  ECORE_Q_FLG_TPA ; 
 int /*<<< orphan*/  ECORE_Q_FLG_TPA_IPV6 ; 
 int /*<<< orphan*/  ECORE_Q_FLG_VLAN ; 
 int IFCAP_LRO ; 
 scalar_t__ IS_MF_SD (struct bxe_softc*) ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned long bxe_get_common_flags (struct bxe_softc*,struct bxe_fastpath*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long
bxe_get_q_flags(struct bxe_softc    *sc,
                struct bxe_fastpath *fp,
                uint8_t             leading)
{
    unsigned long flags = 0;

    if (IS_MF_SD(sc)) {
        bxe_set_bit(ECORE_Q_FLG_OV, &flags);
    }

    if (if_getcapenable(sc->ifp) & IFCAP_LRO) {
        bxe_set_bit(ECORE_Q_FLG_TPA, &flags);
#if __FreeBSD_version >= 800000
        bxe_set_bit(ECORE_Q_FLG_TPA_IPV6, &flags);
#endif
    }

    if (leading) {
        bxe_set_bit(ECORE_Q_FLG_LEADING_RSS, &flags);
        bxe_set_bit(ECORE_Q_FLG_MCAST, &flags);
    }

    bxe_set_bit(ECORE_Q_FLG_VLAN, &flags);

    /* merge with common flags */
    return (flags | bxe_get_common_flags(sc, fp, TRUE));
}