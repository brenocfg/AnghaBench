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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct msk_if_softc {int /*<<< orphan*/  msk_if_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  MSK_SYSCTL_STAT32 (struct msk_if_softc*,struct sysctl_ctx_list*,char*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MSK_SYSCTL_STAT64 (struct msk_if_softc*,struct sysctl_ctx_list*,char*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_bad_octets ; 
 int /*<<< orphan*/  rx_bcast_frames ; 
 int /*<<< orphan*/  rx_crc_errs ; 
 int /*<<< orphan*/  rx_fifo_oflows ; 
 int /*<<< orphan*/  rx_good_octets ; 
 int /*<<< orphan*/  rx_mcast_frames ; 
 int /*<<< orphan*/  rx_pause_frames ; 
 int /*<<< orphan*/  rx_pkts_1024_1518 ; 
 int /*<<< orphan*/  rx_pkts_128_255 ; 
 int /*<<< orphan*/  rx_pkts_1519_max ; 
 int /*<<< orphan*/  rx_pkts_256_511 ; 
 int /*<<< orphan*/  rx_pkts_512_1023 ; 
 int /*<<< orphan*/  rx_pkts_64 ; 
 int /*<<< orphan*/  rx_pkts_65_127 ; 
 int /*<<< orphan*/  rx_pkts_jabbers ; 
 int /*<<< orphan*/  rx_pkts_too_long ; 
 int /*<<< orphan*/  rx_ucast_frames ; 
 int /*<<< orphan*/  tx_bcast_frames ; 
 int /*<<< orphan*/  tx_colls ; 
 int /*<<< orphan*/  tx_excess_colls ; 
 int /*<<< orphan*/  tx_late_colls ; 
 int /*<<< orphan*/  tx_mcast_frames ; 
 int /*<<< orphan*/  tx_multi_colls ; 
 int /*<<< orphan*/  tx_octets ; 
 int /*<<< orphan*/  tx_pause_frames ; 
 int /*<<< orphan*/  tx_pkts_1024_1518 ; 
 int /*<<< orphan*/  tx_pkts_128_255 ; 
 int /*<<< orphan*/  tx_pkts_1519_max ; 
 int /*<<< orphan*/  tx_pkts_256_511 ; 
 int /*<<< orphan*/  tx_pkts_512_1023 ; 
 int /*<<< orphan*/  tx_pkts_64 ; 
 int /*<<< orphan*/  tx_pkts_65_127 ; 
 int /*<<< orphan*/  tx_single_colls ; 
 int /*<<< orphan*/  tx_ucast_frames ; 
 int /*<<< orphan*/  tx_underflows ; 

__attribute__((used)) static void
msk_sysctl_node(struct msk_if_softc *sc_if)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *child, *schild;
	struct sysctl_oid *tree;

	ctx = device_get_sysctl_ctx(sc_if->msk_if_dev);
	child = SYSCTL_CHILDREN(device_get_sysctl_tree(sc_if->msk_if_dev));

	tree = SYSCTL_ADD_NODE(ctx, child, OID_AUTO, "stats", CTLFLAG_RD,
	    NULL, "MSK Statistics");
	schild = SYSCTL_CHILDREN(tree);
	tree = SYSCTL_ADD_NODE(ctx, schild, OID_AUTO, "rx", CTLFLAG_RD,
	    NULL, "MSK RX Statistics");
	child = SYSCTL_CHILDREN(tree);
	MSK_SYSCTL_STAT32(sc_if, ctx, "ucast_frames",
	    child, rx_ucast_frames, "Good unicast frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "bcast_frames",
	    child, rx_bcast_frames, "Good broadcast frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "pause_frames",
	    child, rx_pause_frames, "Pause frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "mcast_frames",
	    child, rx_mcast_frames, "Multicast frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "crc_errs",
	    child, rx_crc_errs, "CRC errors");
	MSK_SYSCTL_STAT64(sc_if, ctx, "good_octets",
	    child, rx_good_octets, "Good octets");
	MSK_SYSCTL_STAT64(sc_if, ctx, "bad_octets",
	    child, rx_bad_octets, "Bad octets");
	MSK_SYSCTL_STAT32(sc_if, ctx, "frames_64",
	    child, rx_pkts_64, "64 bytes frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "frames_65_127",
	    child, rx_pkts_65_127, "65 to 127 bytes frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "frames_128_255",
	    child, rx_pkts_128_255, "128 to 255 bytes frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "frames_256_511",
	    child, rx_pkts_256_511, "256 to 511 bytes frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "frames_512_1023",
	    child, rx_pkts_512_1023, "512 to 1023 bytes frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "frames_1024_1518",
	    child, rx_pkts_1024_1518, "1024 to 1518 bytes frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "frames_1519_max",
	    child, rx_pkts_1519_max, "1519 to max frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "frames_too_long",
	    child, rx_pkts_too_long, "frames too long");
	MSK_SYSCTL_STAT32(sc_if, ctx, "jabbers",
	    child, rx_pkts_jabbers, "Jabber errors");
	MSK_SYSCTL_STAT32(sc_if, ctx, "overflows",
	    child, rx_fifo_oflows, "FIFO overflows");

	tree = SYSCTL_ADD_NODE(ctx, schild, OID_AUTO, "tx", CTLFLAG_RD,
	    NULL, "MSK TX Statistics");
	child = SYSCTL_CHILDREN(tree);
	MSK_SYSCTL_STAT32(sc_if, ctx, "ucast_frames",
	    child, tx_ucast_frames, "Unicast frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "bcast_frames",
	    child, tx_bcast_frames, "Broadcast frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "pause_frames",
	    child, tx_pause_frames, "Pause frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "mcast_frames",
	    child, tx_mcast_frames, "Multicast frames");
	MSK_SYSCTL_STAT64(sc_if, ctx, "octets",
	    child, tx_octets, "Octets");
	MSK_SYSCTL_STAT32(sc_if, ctx, "frames_64",
	    child, tx_pkts_64, "64 bytes frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "frames_65_127",
	    child, tx_pkts_65_127, "65 to 127 bytes frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "frames_128_255",
	    child, tx_pkts_128_255, "128 to 255 bytes frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "frames_256_511",
	    child, tx_pkts_256_511, "256 to 511 bytes frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "frames_512_1023",
	    child, tx_pkts_512_1023, "512 to 1023 bytes frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "frames_1024_1518",
	    child, tx_pkts_1024_1518, "1024 to 1518 bytes frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "frames_1519_max",
	    child, tx_pkts_1519_max, "1519 to max frames");
	MSK_SYSCTL_STAT32(sc_if, ctx, "colls",
	    child, tx_colls, "Collisions");
	MSK_SYSCTL_STAT32(sc_if, ctx, "late_colls",
	    child, tx_late_colls, "Late collisions");
	MSK_SYSCTL_STAT32(sc_if, ctx, "excess_colls",
	    child, tx_excess_colls, "Excessive collisions");
	MSK_SYSCTL_STAT32(sc_if, ctx, "multi_colls",
	    child, tx_multi_colls, "Multiple collisions");
	MSK_SYSCTL_STAT32(sc_if, ctx, "single_colls",
	    child, tx_single_colls, "Single collisions");
	MSK_SYSCTL_STAT32(sc_if, ctx, "underflows",
	    child, tx_underflows, "FIFO underflows");
}