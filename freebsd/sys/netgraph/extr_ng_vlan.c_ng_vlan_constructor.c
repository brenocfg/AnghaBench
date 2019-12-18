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
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_4__ {int /*<<< orphan*/  encap_proto; int /*<<< orphan*/  encap_enable; scalar_t__ decap_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERTYPE_VLAN ; 
 int /*<<< orphan*/  M_NETGRAPH ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  VLAN_ENCAP_FROM_FILTER ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ng_vlan_constructor(node_p node)
{
	priv_p priv;

	priv = malloc(sizeof(*priv), M_NETGRAPH, M_WAITOK | M_ZERO);
	priv->decap_enable = 0;
	priv->encap_enable = VLAN_ENCAP_FROM_FILTER;
	priv->encap_proto = htons(ETHERTYPE_VLAN);
	NG_NODE_SET_PRIVATE(node, priv);
	return (0);
}