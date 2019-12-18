#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* priv_p ;
struct TYPE_4__ {int /*<<< orphan*/  mtu; int /*<<< orphan*/  templ_packets; int /*<<< orphan*/  templ_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASE_MTU ; 
 int /*<<< orphan*/  NETFLOW_V9_MAX_PACKETS_TEMPL ; 
 int /*<<< orphan*/  NETFLOW_V9_MAX_TIME_TEMPL ; 
 int /*<<< orphan*/  generate_v9_templates (TYPE_1__*) ; 

void
ng_netflow_v9_cache_init(priv_p priv)
{
	generate_v9_templates(priv);

	priv->templ_time = NETFLOW_V9_MAX_TIME_TEMPL;
	priv->templ_packets = NETFLOW_V9_MAX_PACKETS_TEMPL;
	priv->mtu = BASE_MTU;
}