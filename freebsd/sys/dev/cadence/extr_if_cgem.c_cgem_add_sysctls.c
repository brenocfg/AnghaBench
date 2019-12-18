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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_udp_csum_errs; int /*<<< orphan*/  rx_tcp_csum_errs; int /*<<< orphan*/  rx_ip_hdr_csum_errs; int /*<<< orphan*/  rx_overrun_errs; int /*<<< orphan*/  rx_resource_errs; int /*<<< orphan*/  rx_align_errs; int /*<<< orphan*/  rx_symbol_errs; int /*<<< orphan*/  rx_frames_length_errs; int /*<<< orphan*/  rx_frames_fcs_errs; int /*<<< orphan*/  rx_frames_jabber; int /*<<< orphan*/  rx_frames_oversize; int /*<<< orphan*/  rx_frames_undersize; int /*<<< orphan*/  rx_frames_1024to1536b; int /*<<< orphan*/  rx_frames_512to1023b; int /*<<< orphan*/  rx_frames_256to511b; int /*<<< orphan*/  rx_frames_128to255b; int /*<<< orphan*/  rx_frames_65to127b; int /*<<< orphan*/  rx_frames_64b; int /*<<< orphan*/  rx_frames_pause; int /*<<< orphan*/  rx_frames_multi; int /*<<< orphan*/  rx_frames_bcast; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_carrier_sense_errs; int /*<<< orphan*/  tx_deferred_frames; int /*<<< orphan*/  tx_late_collisn; int /*<<< orphan*/  tx_excsv_collisn; int /*<<< orphan*/  tx_multi_collisn; int /*<<< orphan*/  tx_single_collisn; int /*<<< orphan*/  tx_under_runs; int /*<<< orphan*/  tx_frames_1024to1536b; int /*<<< orphan*/  tx_frames_512to1023b; int /*<<< orphan*/  tx_frames_256to511b; int /*<<< orphan*/  tx_frames_128to255b; int /*<<< orphan*/  tx_frames_65to127b; int /*<<< orphan*/  tx_frames_64b; int /*<<< orphan*/  tx_frames_pause; int /*<<< orphan*/  tx_frames_multi; int /*<<< orphan*/  tx_frames_bcast; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  tx_bytes; } ;
struct cgem_softc {TYPE_1__ stats; int /*<<< orphan*/  txdefragfails; int /*<<< orphan*/  txdefrags; int /*<<< orphan*/  txdmamapfails; int /*<<< orphan*/  txfull; int /*<<< orphan*/  rxdmamapfails; int /*<<< orphan*/  rxnobufs; int /*<<< orphan*/  rxoverruns; int /*<<< orphan*/  rxhangwar; int /*<<< orphan*/  rxbufs; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UQUAD (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct cgem_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cgem_add_sysctls(device_t dev)
{
	struct cgem_softc *sc = device_get_softc(dev);
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *child;
	struct sysctl_oid *tree;

	ctx = device_get_sysctl_ctx(dev);
	child = SYSCTL_CHILDREN(device_get_sysctl_tree(dev));

	SYSCTL_ADD_INT(ctx, child, OID_AUTO, "rxbufs", CTLFLAG_RW,
		       &sc->rxbufs, 0,
		       "Number receive buffers to provide");

	SYSCTL_ADD_INT(ctx, child, OID_AUTO, "rxhangwar", CTLFLAG_RW,
		       &sc->rxhangwar, 0,
		       "Enable receive hang work-around");

	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "_rxoverruns", CTLFLAG_RD,
			&sc->rxoverruns, 0,
			"Receive overrun events");

	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "_rxnobufs", CTLFLAG_RD,
			&sc->rxnobufs, 0,
			"Receive buf queue empty events");

	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "_rxdmamapfails", CTLFLAG_RD,
			&sc->rxdmamapfails, 0,
			"Receive DMA map failures");

	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "_txfull", CTLFLAG_RD,
			&sc->txfull, 0,
			"Transmit ring full events");

	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "_txdmamapfails", CTLFLAG_RD,
			&sc->txdmamapfails, 0,
			"Transmit DMA map failures");

	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "_txdefrags", CTLFLAG_RD,
			&sc->txdefrags, 0,
			"Transmit m_defrag() calls");

	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "_txdefragfails", CTLFLAG_RD,
			&sc->txdefragfails, 0,
			"Transmit m_defrag() failures");

	tree = SYSCTL_ADD_NODE(ctx, child, OID_AUTO, "stats", CTLFLAG_RD,
			       NULL, "GEM statistics");
	child = SYSCTL_CHILDREN(tree);

	SYSCTL_ADD_UQUAD(ctx, child, OID_AUTO, "tx_bytes", CTLFLAG_RD,
			 &sc->stats.tx_bytes, "Total bytes transmitted");

	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_frames", CTLFLAG_RD,
			&sc->stats.tx_frames, 0, "Total frames transmitted");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_frames_bcast", CTLFLAG_RD,
			&sc->stats.tx_frames_bcast, 0,
			"Number broadcast frames transmitted");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_frames_multi", CTLFLAG_RD,
			&sc->stats.tx_frames_multi, 0,
			"Number multicast frames transmitted");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_frames_pause",
			CTLFLAG_RD, &sc->stats.tx_frames_pause, 0,
			"Number pause frames transmitted");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_frames_64b", CTLFLAG_RD,
			&sc->stats.tx_frames_64b, 0,
			"Number frames transmitted of size 64 bytes or less");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_frames_65to127b", CTLFLAG_RD,
			&sc->stats.tx_frames_65to127b, 0,
			"Number frames transmitted of size 65-127 bytes");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_frames_128to255b",
			CTLFLAG_RD, &sc->stats.tx_frames_128to255b, 0,
			"Number frames transmitted of size 128-255 bytes");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_frames_256to511b",
			CTLFLAG_RD, &sc->stats.tx_frames_256to511b, 0,
			"Number frames transmitted of size 256-511 bytes");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_frames_512to1023b",
			CTLFLAG_RD, &sc->stats.tx_frames_512to1023b, 0,
			"Number frames transmitted of size 512-1023 bytes");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_frames_1024to1536b",
			CTLFLAG_RD, &sc->stats.tx_frames_1024to1536b, 0,
			"Number frames transmitted of size 1024-1536 bytes");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_under_runs",
			CTLFLAG_RD, &sc->stats.tx_under_runs, 0,
			"Number transmit under-run events");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_single_collisn",
			CTLFLAG_RD, &sc->stats.tx_single_collisn, 0,
			"Number single-collision transmit frames");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_multi_collisn",
			CTLFLAG_RD, &sc->stats.tx_multi_collisn, 0,
			"Number multi-collision transmit frames");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_excsv_collisn",
			CTLFLAG_RD, &sc->stats.tx_excsv_collisn, 0,
			"Number excessive collision transmit frames");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_late_collisn",
			CTLFLAG_RD, &sc->stats.tx_late_collisn, 0,
			"Number late-collision transmit frames");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_deferred_frames",
			CTLFLAG_RD, &sc->stats.tx_deferred_frames, 0,
			"Number deferred transmit frames");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_carrier_sense_errs",
			CTLFLAG_RD, &sc->stats.tx_carrier_sense_errs, 0,
			"Number carrier sense errors on transmit");

	SYSCTL_ADD_UQUAD(ctx, child, OID_AUTO, "rx_bytes", CTLFLAG_RD,
			 &sc->stats.rx_bytes, "Total bytes received");

	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_frames", CTLFLAG_RD,
			&sc->stats.rx_frames, 0, "Total frames received");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_frames_bcast",
			CTLFLAG_RD, &sc->stats.rx_frames_bcast, 0,
			"Number broadcast frames received");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_frames_multi",
			CTLFLAG_RD, &sc->stats.rx_frames_multi, 0,
			"Number multicast frames received");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_frames_pause",
			CTLFLAG_RD, &sc->stats.rx_frames_pause, 0,
			"Number pause frames received");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_frames_64b",
			CTLFLAG_RD, &sc->stats.rx_frames_64b, 0,
			"Number frames received of size 64 bytes or less");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_frames_65to127b",
			CTLFLAG_RD, &sc->stats.rx_frames_65to127b, 0,
			"Number frames received of size 65-127 bytes");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_frames_128to255b",
			CTLFLAG_RD, &sc->stats.rx_frames_128to255b, 0,
			"Number frames received of size 128-255 bytes");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_frames_256to511b",
			CTLFLAG_RD, &sc->stats.rx_frames_256to511b, 0,
			"Number frames received of size 256-511 bytes");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_frames_512to1023b",
			CTLFLAG_RD, &sc->stats.rx_frames_512to1023b, 0,
			"Number frames received of size 512-1023 bytes");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_frames_1024to1536b",
			CTLFLAG_RD, &sc->stats.rx_frames_1024to1536b, 0,
			"Number frames received of size 1024-1536 bytes");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_frames_undersize",
			CTLFLAG_RD, &sc->stats.rx_frames_undersize, 0,
			"Number undersize frames received");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_frames_oversize",
			CTLFLAG_RD, &sc->stats.rx_frames_oversize, 0,
			"Number oversize frames received");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_frames_jabber",
			CTLFLAG_RD, &sc->stats.rx_frames_jabber, 0,
			"Number jabber frames received");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_frames_fcs_errs",
			CTLFLAG_RD, &sc->stats.rx_frames_fcs_errs, 0,
			"Number frames received with FCS errors");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_frames_length_errs",
			CTLFLAG_RD, &sc->stats.rx_frames_length_errs, 0,
			"Number frames received with length errors");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_symbol_errs",
			CTLFLAG_RD, &sc->stats.rx_symbol_errs, 0,
			"Number receive symbol errors");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_align_errs",
			CTLFLAG_RD, &sc->stats.rx_align_errs, 0,
			"Number receive alignment errors");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_resource_errs",
			CTLFLAG_RD, &sc->stats.rx_resource_errs, 0,
			"Number frames received when no rx buffer available");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_overrun_errs",
			CTLFLAG_RD, &sc->stats.rx_overrun_errs, 0,
			"Number frames received but not copied due to "
			"receive overrun");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_frames_ip_hdr_csum_errs",
			CTLFLAG_RD, &sc->stats.rx_ip_hdr_csum_errs, 0,
			"Number frames received with IP header checksum "
			"errors");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_frames_tcp_csum_errs",
			CTLFLAG_RD, &sc->stats.rx_tcp_csum_errs, 0,
			"Number frames received with TCP checksum errors");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_frames_udp_csum_errs",
			CTLFLAG_RD, &sc->stats.rx_udp_csum_errs, 0,
			"Number frames received with UDP checksum errors");
}