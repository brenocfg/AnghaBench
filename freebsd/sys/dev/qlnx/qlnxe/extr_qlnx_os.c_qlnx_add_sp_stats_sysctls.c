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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  sp_interrupts; int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_QUAD (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qlnx_add_sp_stats_sysctls(qlnx_host_t *ha)
{
        struct sysctl_ctx_list	*ctx;
        struct sysctl_oid_list	*children;
	struct sysctl_oid	*ctx_oid;

        ctx = device_get_sysctl_ctx(ha->pci_dev);
	children = SYSCTL_CHILDREN(device_get_sysctl_tree(ha->pci_dev));

	ctx_oid = SYSCTL_ADD_NODE(ctx, children, OID_AUTO, "spstat",
			CTLFLAG_RD, NULL, "spstat");
        children = SYSCTL_CHILDREN(ctx_oid);

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "sp_interrupts",
                CTLFLAG_RD, &ha->sp_interrupts,
                "No. of slowpath interrupts");

	return;
}