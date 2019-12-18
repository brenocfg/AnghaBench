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
struct sfe_ipv6_connection_match {scalar_t__ rx_byte_count; int /*<<< orphan*/  rx_byte_count64; scalar_t__ rx_packet_count; int /*<<< orphan*/  rx_packet_count64; } ;

/* Variables and functions */

__attribute__((used)) static inline void sfe_ipv6_connection_match_update_summary_stats(struct sfe_ipv6_connection_match *cm)
{
	cm->rx_packet_count64 += cm->rx_packet_count;
	cm->rx_packet_count = 0;
	cm->rx_byte_count64 += cm->rx_byte_count;
	cm->rx_byte_count = 0;
}