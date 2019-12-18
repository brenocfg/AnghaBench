#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ng_netflow_v9info {int /*<<< orphan*/  mtu; int /*<<< orphan*/  templ_packets; int /*<<< orphan*/  templ_time; } ;
typedef  TYPE_1__* priv_p ;
struct TYPE_3__ {int /*<<< orphan*/  mtu; int /*<<< orphan*/  templ_packets; int /*<<< orphan*/  templ_time; } ;

/* Variables and functions */

void
ng_netflow_copyv9info(priv_p priv, struct ng_netflow_v9info *i)
{

	i->templ_time = priv->templ_time;
	i->templ_packets = priv->templ_packets;
	i->mtu = priv->mtu;
}