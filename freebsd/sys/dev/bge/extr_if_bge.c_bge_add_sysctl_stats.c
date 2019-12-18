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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct bge_softc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  outRangeLengthError; int /*<<< orphan*/  inRangeLengthError; int /*<<< orphan*/  etherStatsUndersizePkts; int /*<<< orphan*/  etherStatsJabbers; int /*<<< orphan*/  dot3StatsFramesTooLong; int /*<<< orphan*/  xoffStateEntered; int /*<<< orphan*/  macControlFramesReceived; int /*<<< orphan*/  xoffPauseFramesReceived; int /*<<< orphan*/  xonPauseFramesReceived; int /*<<< orphan*/  dot3StatsAlignmentErrors; int /*<<< orphan*/  dot3StatsFCSErrors; int /*<<< orphan*/  ifHCInMulticastPkts; int /*<<< orphan*/  ifHCInUcastPkts; int /*<<< orphan*/  etherStatsFragments; int /*<<< orphan*/  ifHCInOctets; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifOutErrors; int /*<<< orphan*/  ifOutDiscards; int /*<<< orphan*/  dot3StatsCarrierSenseErrors; int /*<<< orphan*/  ifHCOutBroadcastPkts; int /*<<< orphan*/  ifHCOutMulticastPkts; int /*<<< orphan*/  ifHCOutUcastPkts; int /*<<< orphan*/  dot3StatsLateCollisions; int /*<<< orphan*/  dot3StatsExcessiveCollisions; int /*<<< orphan*/  dot3StatsDeferredTransmissions; int /*<<< orphan*/  dot3StatsMultipleCollisionFrames; int /*<<< orphan*/  dot3StatsSingleCollisionFrames; int /*<<< orphan*/  dot3StatsInternalMacTransmitErrors; int /*<<< orphan*/  flowControlDone; int /*<<< orphan*/  outXoffSent; int /*<<< orphan*/  outXonSent; int /*<<< orphan*/  etherStatsCollisions; int /*<<< orphan*/  ifHCOutOctets; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGE_SYSCTL_STAT (struct bge_softc*,struct sysctl_ctx_list*,char*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  COSFramesDroppedDueToFilters ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  ifInDiscards ; 
 int /*<<< orphan*/  ifInErrors ; 
 int /*<<< orphan*/  nicAvoidedInterrupts ; 
 int /*<<< orphan*/  nicDmaReadHighPriQueueFull ; 
 int /*<<< orphan*/  nicDmaReadQueueFull ; 
 int /*<<< orphan*/  nicDmaWriteHighPriQueueFull ; 
 int /*<<< orphan*/  nicDmaWriteQueueFull ; 
 int /*<<< orphan*/  nicInterrupts ; 
 int /*<<< orphan*/  nicNoMoreRxBDs ; 
 int /*<<< orphan*/  nicRecvThresholdHit ; 
 int /*<<< orphan*/  nicRingSetSendProdIndex ; 
 int /*<<< orphan*/  nicRingStatusUpdate ; 
 int /*<<< orphan*/  nicSendDataCompQueueFull ; 
 int /*<<< orphan*/  nicSendThresholdHit ; 
 TYPE_2__ rxstats ; 
 TYPE_1__ txstats ; 

__attribute__((used)) static void
bge_add_sysctl_stats(struct bge_softc *sc, struct sysctl_ctx_list *ctx,
    struct sysctl_oid_list *parent)
{
	struct sysctl_oid *tree;
	struct sysctl_oid_list *children, *schildren;

	tree = SYSCTL_ADD_NODE(ctx, parent, OID_AUTO, "stats", CTLFLAG_RD,
	    NULL, "BGE Statistics");
	schildren = children = SYSCTL_CHILDREN(tree);
	BGE_SYSCTL_STAT(sc, ctx, "Frames Dropped Due To Filters",
	    children, COSFramesDroppedDueToFilters,
	    "FramesDroppedDueToFilters");
	BGE_SYSCTL_STAT(sc, ctx, "NIC DMA Write Queue Full",
	    children, nicDmaWriteQueueFull, "DmaWriteQueueFull");
	BGE_SYSCTL_STAT(sc, ctx, "NIC DMA Write High Priority Queue Full",
	    children, nicDmaWriteHighPriQueueFull, "DmaWriteHighPriQueueFull");
	BGE_SYSCTL_STAT(sc, ctx, "NIC No More RX Buffer Descriptors",
	    children, nicNoMoreRxBDs, "NoMoreRxBDs");
	BGE_SYSCTL_STAT(sc, ctx, "Discarded Input Frames",
	    children, ifInDiscards, "InputDiscards");
	BGE_SYSCTL_STAT(sc, ctx, "Input Errors",
	    children, ifInErrors, "InputErrors");
	BGE_SYSCTL_STAT(sc, ctx, "NIC Recv Threshold Hit",
	    children, nicRecvThresholdHit, "RecvThresholdHit");
	BGE_SYSCTL_STAT(sc, ctx, "NIC DMA Read Queue Full",
	    children, nicDmaReadQueueFull, "DmaReadQueueFull");
	BGE_SYSCTL_STAT(sc, ctx, "NIC DMA Read High Priority Queue Full",
	    children, nicDmaReadHighPriQueueFull, "DmaReadHighPriQueueFull");
	BGE_SYSCTL_STAT(sc, ctx, "NIC Send Data Complete Queue Full",
	    children, nicSendDataCompQueueFull, "SendDataCompQueueFull");
	BGE_SYSCTL_STAT(sc, ctx, "NIC Ring Set Send Producer Index",
	    children, nicRingSetSendProdIndex, "RingSetSendProdIndex");
	BGE_SYSCTL_STAT(sc, ctx, "NIC Ring Status Update",
	    children, nicRingStatusUpdate, "RingStatusUpdate");
	BGE_SYSCTL_STAT(sc, ctx, "NIC Interrupts",
	    children, nicInterrupts, "Interrupts");
	BGE_SYSCTL_STAT(sc, ctx, "NIC Avoided Interrupts",
	    children, nicAvoidedInterrupts, "AvoidedInterrupts");
	BGE_SYSCTL_STAT(sc, ctx, "NIC Send Threshold Hit",
	    children, nicSendThresholdHit, "SendThresholdHit");

	tree = SYSCTL_ADD_NODE(ctx, schildren, OID_AUTO, "rx", CTLFLAG_RD,
	    NULL, "BGE RX Statistics");
	children = SYSCTL_CHILDREN(tree);
	BGE_SYSCTL_STAT(sc, ctx, "Inbound Octets",
	    children, rxstats.ifHCInOctets, "ifHCInOctets");
	BGE_SYSCTL_STAT(sc, ctx, "Fragments",
	    children, rxstats.etherStatsFragments, "Fragments");
	BGE_SYSCTL_STAT(sc, ctx, "Inbound Unicast Packets",
	    children, rxstats.ifHCInUcastPkts, "UnicastPkts");
	BGE_SYSCTL_STAT(sc, ctx, "Inbound Multicast Packets",
	    children, rxstats.ifHCInMulticastPkts, "MulticastPkts");
	BGE_SYSCTL_STAT(sc, ctx, "FCS Errors",
	    children, rxstats.dot3StatsFCSErrors, "FCSErrors");
	BGE_SYSCTL_STAT(sc, ctx, "Alignment Errors",
	    children, rxstats.dot3StatsAlignmentErrors, "AlignmentErrors");
	BGE_SYSCTL_STAT(sc, ctx, "XON Pause Frames Received",
	    children, rxstats.xonPauseFramesReceived, "xonPauseFramesReceived");
	BGE_SYSCTL_STAT(sc, ctx, "XOFF Pause Frames Received",
	    children, rxstats.xoffPauseFramesReceived,
	    "xoffPauseFramesReceived");
	BGE_SYSCTL_STAT(sc, ctx, "MAC Control Frames Received",
	    children, rxstats.macControlFramesReceived,
	    "ControlFramesReceived");
	BGE_SYSCTL_STAT(sc, ctx, "XOFF State Entered",
	    children, rxstats.xoffStateEntered, "xoffStateEntered");
	BGE_SYSCTL_STAT(sc, ctx, "Frames Too Long",
	    children, rxstats.dot3StatsFramesTooLong, "FramesTooLong");
	BGE_SYSCTL_STAT(sc, ctx, "Jabbers",
	    children, rxstats.etherStatsJabbers, "Jabbers");
	BGE_SYSCTL_STAT(sc, ctx, "Undersized Packets",
	    children, rxstats.etherStatsUndersizePkts, "UndersizePkts");
	BGE_SYSCTL_STAT(sc, ctx, "Inbound Range Length Errors",
	    children, rxstats.inRangeLengthError, "inRangeLengthError");
	BGE_SYSCTL_STAT(sc, ctx, "Outbound Range Length Errors",
	    children, rxstats.outRangeLengthError, "outRangeLengthError");

	tree = SYSCTL_ADD_NODE(ctx, schildren, OID_AUTO, "tx", CTLFLAG_RD,
	    NULL, "BGE TX Statistics");
	children = SYSCTL_CHILDREN(tree);
	BGE_SYSCTL_STAT(sc, ctx, "Outbound Octets",
	    children, txstats.ifHCOutOctets, "ifHCOutOctets");
	BGE_SYSCTL_STAT(sc, ctx, "TX Collisions",
	    children, txstats.etherStatsCollisions, "Collisions");
	BGE_SYSCTL_STAT(sc, ctx, "XON Sent",
	    children, txstats.outXonSent, "XonSent");
	BGE_SYSCTL_STAT(sc, ctx, "XOFF Sent",
	    children, txstats.outXoffSent, "XoffSent");
	BGE_SYSCTL_STAT(sc, ctx, "Flow Control Done",
	    children, txstats.flowControlDone, "flowControlDone");
	BGE_SYSCTL_STAT(sc, ctx, "Internal MAC TX errors",
	    children, txstats.dot3StatsInternalMacTransmitErrors,
	    "InternalMacTransmitErrors");
	BGE_SYSCTL_STAT(sc, ctx, "Single Collision Frames",
	    children, txstats.dot3StatsSingleCollisionFrames,
	    "SingleCollisionFrames");
	BGE_SYSCTL_STAT(sc, ctx, "Multiple Collision Frames",
	    children, txstats.dot3StatsMultipleCollisionFrames,
	    "MultipleCollisionFrames");
	BGE_SYSCTL_STAT(sc, ctx, "Deferred Transmissions",
	    children, txstats.dot3StatsDeferredTransmissions,
	    "DeferredTransmissions");
	BGE_SYSCTL_STAT(sc, ctx, "Excessive Collisions",
	    children, txstats.dot3StatsExcessiveCollisions,
	    "ExcessiveCollisions");
	BGE_SYSCTL_STAT(sc, ctx, "Late Collisions",
	    children, txstats.dot3StatsLateCollisions,
	    "LateCollisions");
	BGE_SYSCTL_STAT(sc, ctx, "Outbound Unicast Packets",
	    children, txstats.ifHCOutUcastPkts, "UnicastPkts");
	BGE_SYSCTL_STAT(sc, ctx, "Outbound Multicast Packets",
	    children, txstats.ifHCOutMulticastPkts, "MulticastPkts");
	BGE_SYSCTL_STAT(sc, ctx, "Outbound Broadcast Packets",
	    children, txstats.ifHCOutBroadcastPkts, "BroadcastPkts");
	BGE_SYSCTL_STAT(sc, ctx, "Carrier Sense Errors",
	    children, txstats.dot3StatsCarrierSenseErrors,
	    "CarrierSenseErrors");
	BGE_SYSCTL_STAT(sc, ctx, "Outbound Discards",
	    children, txstats.ifOutDiscards, "Discards");
	BGE_SYSCTL_STAT(sc, ctx, "Outbound Errors",
	    children, txstats.ifOutErrors, "Errors");
}