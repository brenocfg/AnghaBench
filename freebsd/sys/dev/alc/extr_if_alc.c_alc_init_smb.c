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
struct TYPE_2__ {int /*<<< orphan*/  alc_smb_map; int /*<<< orphan*/  alc_smb_tag; } ;
struct alc_ring_data {int /*<<< orphan*/  alc_smb; } ;
struct alc_softc {TYPE_1__ alc_cdata; struct alc_ring_data alc_rdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC_LOCK_ASSERT (struct alc_softc*) ; 
 int /*<<< orphan*/  ALC_SMB_SZ ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
alc_init_smb(struct alc_softc *sc)
{
	struct alc_ring_data *rd;

	ALC_LOCK_ASSERT(sc);

	rd = &sc->alc_rdata;
	bzero(rd->alc_smb, ALC_SMB_SZ);
	bus_dmamap_sync(sc->alc_cdata.alc_smb_tag, sc->alc_cdata.alc_smb_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
}