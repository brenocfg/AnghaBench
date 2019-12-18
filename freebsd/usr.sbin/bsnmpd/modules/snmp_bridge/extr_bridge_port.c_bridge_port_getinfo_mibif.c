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
struct TYPE_3__ {int /*<<< orphan*/  ifi_iqdrops; int /*<<< orphan*/  ifi_opackets; int /*<<< orphan*/  ifi_ipackets; int /*<<< orphan*/  ifi_mtu; } ;
struct TYPE_4__ {TYPE_1__ ifmd_data; } ;
struct mibif {TYPE_2__ mib; } ;
struct bridge_port {int /*<<< orphan*/  in_drops; int /*<<< orphan*/  out_frames; int /*<<< orphan*/  in_frames; int /*<<< orphan*/  max_info; } ;

/* Variables and functions */

void
bridge_port_getinfo_mibif(struct mibif *m_if, struct bridge_port *bp)
{
	bp->max_info = m_if->mib.ifmd_data.ifi_mtu;
	bp->in_frames = m_if->mib.ifmd_data.ifi_ipackets;
	bp->out_frames = m_if->mib.ifmd_data.ifi_opackets;
	bp->in_drops = m_if->mib.ifmd_data.ifi_iqdrops;
}