#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct mii_data {int /*<<< orphan*/  mii_media_active; } ;
struct TYPE_6__ {int /*<<< orphan*/  miibus; } ;
typedef  TYPE_1__ ae_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  AE_LOCK_ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  AE_MAC_FULL_DUPLEX ; 
 int /*<<< orphan*/  AE_MAC_REG ; 
 int /*<<< orphan*/  AE_READ_4 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_WRITE_4 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFM_FDX ; 
 int IFM_OPTIONS (int /*<<< orphan*/ ) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ae_mac_config(ae_softc_t *sc)
{
	struct mii_data *mii;
	uint32_t val;

	AE_LOCK_ASSERT(sc);

	mii = device_get_softc(sc->miibus);
	val = AE_READ_4(sc, AE_MAC_REG);
	val &= ~AE_MAC_FULL_DUPLEX;
	/* XXX disable AE_MAC_TX_FLOW_EN? */

	if ((IFM_OPTIONS(mii->mii_media_active) & IFM_FDX) != 0)
		val |= AE_MAC_FULL_DUPLEX;

	AE_WRITE_4(sc, AE_MAC_REG, val);
}