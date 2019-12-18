#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct TYPE_11__ {int /*<<< orphan*/  max_end; int /*<<< orphan*/  end; int /*<<< orphan*/  max_win; } ;
struct TYPE_12__ {TYPE_5__ tcp; } ;
struct sfe_ipv4_connection_match {int /*<<< orphan*/  rx_byte_count64; int /*<<< orphan*/  rx_packet_count64; int /*<<< orphan*/  match_dev; int /*<<< orphan*/  rx_byte_count; int /*<<< orphan*/  rx_packet_count; TYPE_6__ protocol_state; } ;
struct sfe_ipv4_connection {void* last_sync_jiffies; struct sfe_ipv4_connection_match* reply_match; struct sfe_ipv4_connection_match* original_match; int /*<<< orphan*/  dest_port_xlate; int /*<<< orphan*/  dest_port; int /*<<< orphan*/  src_port_xlate; int /*<<< orphan*/  src_port; int /*<<< orphan*/  dest_ip_xlate; int /*<<< orphan*/  dest_ip; int /*<<< orphan*/  src_ip_xlate; int /*<<< orphan*/  src_ip; int /*<<< orphan*/  protocol; } ;
struct sfe_ipv4 {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  ip; } ;
struct TYPE_9__ {int /*<<< orphan*/  ip; } ;
struct TYPE_8__ {int /*<<< orphan*/  ip; } ;
struct TYPE_7__ {int /*<<< orphan*/  ip; } ;
struct sfe_connection_sync {void* delta_jiffies; int /*<<< orphan*/  reason; int /*<<< orphan*/  dest_byte_count; int /*<<< orphan*/  dest_packet_count; int /*<<< orphan*/  dest_dev; int /*<<< orphan*/  src_byte_count; int /*<<< orphan*/  src_packet_count; int /*<<< orphan*/  src_dev; int /*<<< orphan*/  dest_new_byte_count; int /*<<< orphan*/  dest_new_packet_count; int /*<<< orphan*/  src_new_byte_count; int /*<<< orphan*/  src_new_packet_count; int /*<<< orphan*/  dest_td_max_end; int /*<<< orphan*/  dest_td_end; int /*<<< orphan*/  dest_td_max_window; int /*<<< orphan*/  src_td_max_end; int /*<<< orphan*/  src_td_end; int /*<<< orphan*/  src_td_max_window; int /*<<< orphan*/  dest_port_xlate; int /*<<< orphan*/  dest_port; int /*<<< orphan*/  src_port_xlate; int /*<<< orphan*/  src_port; TYPE_4__ dest_ip_xlate; TYPE_3__ dest_ip; TYPE_2__ src_ip_xlate; TYPE_1__ src_ip; int /*<<< orphan*/  protocol; scalar_t__ is_v6; } ;
typedef  int /*<<< orphan*/  sfe_sync_reason_t ;

/* Variables and functions */
 int /*<<< orphan*/  sfe_ipv4_connection_match_update_summary_stats (struct sfe_ipv4_connection_match*) ; 

__attribute__((used)) static void sfe_ipv4_gen_sync_sfe_ipv4_connection(struct sfe_ipv4 *si, struct sfe_ipv4_connection *c,
						  struct sfe_connection_sync *sis, sfe_sync_reason_t reason,
						  u64 now_jiffies)
{
	struct sfe_ipv4_connection_match *original_cm;
	struct sfe_ipv4_connection_match *reply_cm;

	/*
	 * Fill in the update message.
	 */
	sis->is_v6 = 0;
	sis->protocol = c->protocol;
	sis->src_ip.ip = c->src_ip;
	sis->src_ip_xlate.ip = c->src_ip_xlate;
	sis->dest_ip.ip = c->dest_ip;
	sis->dest_ip_xlate.ip = c->dest_ip_xlate;
	sis->src_port = c->src_port;
	sis->src_port_xlate = c->src_port_xlate;
	sis->dest_port = c->dest_port;
	sis->dest_port_xlate = c->dest_port_xlate;

	original_cm = c->original_match;
	reply_cm = c->reply_match;
	sis->src_td_max_window = original_cm->protocol_state.tcp.max_win;
	sis->src_td_end = original_cm->protocol_state.tcp.end;
	sis->src_td_max_end = original_cm->protocol_state.tcp.max_end;
	sis->dest_td_max_window = reply_cm->protocol_state.tcp.max_win;
	sis->dest_td_end = reply_cm->protocol_state.tcp.end;
	sis->dest_td_max_end = reply_cm->protocol_state.tcp.max_end;

	sis->src_new_packet_count = original_cm->rx_packet_count;
	sis->src_new_byte_count = original_cm->rx_byte_count;
	sis->dest_new_packet_count = reply_cm->rx_packet_count;
	sis->dest_new_byte_count = reply_cm->rx_byte_count;

	sfe_ipv4_connection_match_update_summary_stats(original_cm);
	sfe_ipv4_connection_match_update_summary_stats(reply_cm);

	sis->src_dev = original_cm->match_dev;
	sis->src_packet_count = original_cm->rx_packet_count64;
	sis->src_byte_count = original_cm->rx_byte_count64;

	sis->dest_dev = reply_cm->match_dev;
	sis->dest_packet_count = reply_cm->rx_packet_count64;
	sis->dest_byte_count = reply_cm->rx_byte_count64;

	sis->reason = reason;

	/*
	 * Get the time increment since our last sync.
	 */
	sis->delta_jiffies = now_jiffies - c->last_sync_jiffies;
	c->last_sync_jiffies = now_jiffies;
}