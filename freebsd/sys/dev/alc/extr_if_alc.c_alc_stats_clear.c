#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct smb {int /*<<< orphan*/  tx_mcast_bytes; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  rx_pkts_filtered; int /*<<< orphan*/  rx_frames; scalar_t__ updated; } ;
struct TYPE_4__ {int /*<<< orphan*/  alc_smb_map; int /*<<< orphan*/  alc_smb_tag; } ;
struct TYPE_3__ {struct smb* alc_smb; } ;
struct alc_softc {int alc_flags; TYPE_2__ alc_cdata; TYPE_1__ alc_rdata; } ;

/* Variables and functions */
 int ALC_FLAG_SMB_BUG ; 
 scalar_t__ ALC_RX_MIB_BASE ; 
 scalar_t__ ALC_TX_MIB_BASE ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CSR_READ_4 (struct alc_softc*,scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
alc_stats_clear(struct alc_softc *sc)
{
	struct smb sb, *smb;
	uint32_t *reg;
	int i;

	if ((sc->alc_flags & ALC_FLAG_SMB_BUG) == 0) {
		bus_dmamap_sync(sc->alc_cdata.alc_smb_tag,
		    sc->alc_cdata.alc_smb_map,
		    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
		smb = sc->alc_rdata.alc_smb;
		/* Update done, clear. */
		smb->updated = 0;
		bus_dmamap_sync(sc->alc_cdata.alc_smb_tag,
		    sc->alc_cdata.alc_smb_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	} else {
		for (reg = &sb.rx_frames, i = 0; reg <= &sb.rx_pkts_filtered;
		    reg++) {
			CSR_READ_4(sc, ALC_RX_MIB_BASE + i);
			i += sizeof(uint32_t);
		}
		/* Read Tx statistics. */
		for (reg = &sb.tx_frames, i = 0; reg <= &sb.tx_mcast_bytes;
		    reg++) {
			CSR_READ_4(sc, ALC_TX_MIB_BASE + i);
			i += sizeof(uint32_t);
		}
	}
}