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
struct ixl_vsi {int /*<<< orphan*/  ctx; } ;
struct i40e_hw_port_stats {int dummy; } ;
struct ixl_pf {int /*<<< orphan*/  admin_irq; struct i40e_hw_port_stats stats; struct ixl_vsi vsi; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_UQUAD (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_add_queues_sysctls (int /*<<< orphan*/ ,struct ixl_vsi*) ; 
 int /*<<< orphan*/  ixl_add_sysctls_mac_stats (struct sysctl_ctx_list*,struct sysctl_oid_list*,struct i40e_hw_port_stats*) ; 
 int /*<<< orphan*/  ixl_add_vsi_sysctls (int /*<<< orphan*/ ,struct ixl_vsi*,struct sysctl_ctx_list*,char*) ; 

void
ixl_add_hw_stats(struct ixl_pf *pf)
{
	struct ixl_vsi *vsi = &pf->vsi;
	device_t dev = iflib_get_dev(vsi->ctx);
	struct i40e_hw_port_stats *pf_stats = &pf->stats;

	struct sysctl_ctx_list *ctx = device_get_sysctl_ctx(dev);
	struct sysctl_oid *tree = device_get_sysctl_tree(dev);
	struct sysctl_oid_list *child = SYSCTL_CHILDREN(tree);

	/* Driver statistics */
	SYSCTL_ADD_UQUAD(ctx, child, OID_AUTO, "admin_irq",
			CTLFLAG_RD, &pf->admin_irq,
			"Admin Queue IRQs received");

	ixl_add_vsi_sysctls(dev, vsi, ctx, "pf");

	ixl_add_queues_sysctls(dev, vsi);

	ixl_add_sysctls_mac_stats(ctx, child, pf_stats);
}