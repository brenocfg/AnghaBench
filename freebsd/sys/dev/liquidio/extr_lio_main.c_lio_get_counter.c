#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_14__ {scalar_t__ frame_err; scalar_t__ l2_err; scalar_t__ fcs_err; scalar_t__ total_mcst; } ;
struct TYPE_13__ {scalar_t__ total_collisions; scalar_t__ mcast_pkts_sent; } ;
struct TYPE_15__ {TYPE_11__ fromwire; TYPE_10__ fromhost; } ;
struct octeon_device {int num_oqs; int num_iqs; TYPE_12__ link_stats; TYPE_9__** instr_queue; TYPE_4__** droq; } ;
struct TYPE_22__ {TYPE_6__* txpciq; TYPE_2__* rxpciq; } ;
struct lio {TYPE_7__ linfo; struct octeon_device* oct_dev; } ;
typedef  int ift_counter ;
typedef  int /*<<< orphan*/  if_t ;
struct TYPE_23__ {scalar_t__ tx_dropped; scalar_t__ tx_tot_bytes; scalar_t__ tx_done; } ;
struct TYPE_24__ {TYPE_8__ stats; } ;
struct TYPE_20__ {int q_no; } ;
struct TYPE_21__ {TYPE_5__ s; } ;
struct TYPE_18__ {scalar_t__ rx_dropped; scalar_t__ rx_bytes_received; scalar_t__ rx_pkts_received; } ;
struct TYPE_19__ {TYPE_3__ stats; } ;
struct TYPE_16__ {int q_no; } ;
struct TYPE_17__ {TYPE_1__ s; } ;

/* Variables and functions */
#define  IFCOUNTER_COLLISIONS 137 
#define  IFCOUNTER_IBYTES 136 
#define  IFCOUNTER_IERRORS 135 
#define  IFCOUNTER_IMCASTS 134 
#define  IFCOUNTER_IPACKETS 133 
#define  IFCOUNTER_IQDROPS 132 
#define  IFCOUNTER_OBYTES 131 
#define  IFCOUNTER_OMCASTS 130 
#define  IFCOUNTER_OPACKETS 129 
#define  IFCOUNTER_OQDROPS 128 
 scalar_t__ if_get_counter_default (int /*<<< orphan*/ ,int) ; 
 struct lio* if_getsoftc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
lio_get_counter(if_t ifp, ift_counter cnt)
{
	struct lio	*lio = if_getsoftc(ifp);
	struct octeon_device	*oct = lio->oct_dev;
	uint64_t	counter = 0;
	int		i, q_no;

	switch (cnt) {
	case IFCOUNTER_IPACKETS:
		for (i = 0; i < oct->num_oqs; i++) {
			q_no = lio->linfo.rxpciq[i].s.q_no;
			counter += oct->droq[q_no]->stats.rx_pkts_received;
		}
		break;
	case IFCOUNTER_OPACKETS:
		for (i = 0; i < oct->num_iqs; i++) {
			q_no = lio->linfo.txpciq[i].s.q_no;
			counter += oct->instr_queue[q_no]->stats.tx_done;
		}
		break;
	case IFCOUNTER_IBYTES:
		for (i = 0; i < oct->num_oqs; i++) {
			q_no = lio->linfo.rxpciq[i].s.q_no;
			counter += oct->droq[q_no]->stats.rx_bytes_received;
		}
		break;
	case IFCOUNTER_OBYTES:
		for (i = 0; i < oct->num_iqs; i++) {
			q_no = lio->linfo.txpciq[i].s.q_no;
			counter += oct->instr_queue[q_no]->stats.tx_tot_bytes;
		}
		break;
	case IFCOUNTER_IQDROPS:
		for (i = 0; i < oct->num_oqs; i++) {
			q_no = lio->linfo.rxpciq[i].s.q_no;
			counter += oct->droq[q_no]->stats.rx_dropped;
		}
		break;
	case IFCOUNTER_OQDROPS:
		for (i = 0; i < oct->num_iqs; i++) {
			q_no = lio->linfo.txpciq[i].s.q_no;
			counter += oct->instr_queue[q_no]->stats.tx_dropped;
		}
		break;
	case IFCOUNTER_IMCASTS:
		counter = oct->link_stats.fromwire.total_mcst;
		break;
	case IFCOUNTER_OMCASTS:
		counter = oct->link_stats.fromhost.mcast_pkts_sent;
		break;
	case IFCOUNTER_COLLISIONS:
		counter = oct->link_stats.fromhost.total_collisions;
		break;
	case IFCOUNTER_IERRORS:
		counter = oct->link_stats.fromwire.fcs_err +
		    oct->link_stats.fromwire.l2_err +
		    oct->link_stats.fromwire.frame_err;
		break;
	default:
		return (if_get_counter_default(ifp, cnt));
	}

	return (counter);
}