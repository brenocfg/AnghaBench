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
typedef  int /*<<< orphan*/  uint32_t ;
struct nfe_softc {int nfe_flags; } ;

/* Variables and functions */
 int NFE_MIB_V1 ; 
 int NFE_MIB_V2 ; 
 int NFE_MIB_V3 ; 
 int NFE_NUM_MIB_STATV1 ; 
 int NFE_NUM_MIB_STATV2 ; 
 int /*<<< orphan*/  NFE_READ (struct nfe_softc*,scalar_t__) ; 
 scalar_t__ NFE_TX_BROADCAST ; 
 scalar_t__ NFE_TX_MULTICAST ; 
 scalar_t__ NFE_TX_OCTET ; 
 scalar_t__ NFE_TX_UNICAST ; 

__attribute__((used)) static void
nfe_stats_clear(struct nfe_softc *sc)
{
	int i, mib_cnt;

	if ((sc->nfe_flags & NFE_MIB_V1) != 0)
		mib_cnt = NFE_NUM_MIB_STATV1;
	else if ((sc->nfe_flags & (NFE_MIB_V2 | NFE_MIB_V3)) != 0)
		mib_cnt = NFE_NUM_MIB_STATV2;
	else
		return;

	for (i = 0; i < mib_cnt; i++)
		NFE_READ(sc, NFE_TX_OCTET + i * sizeof(uint32_t));

	if ((sc->nfe_flags & NFE_MIB_V3) != 0) {
		NFE_READ(sc, NFE_TX_UNICAST);
		NFE_READ(sc, NFE_TX_MULTICAST);
		NFE_READ(sc, NFE_TX_BROADCAST);
	}
}