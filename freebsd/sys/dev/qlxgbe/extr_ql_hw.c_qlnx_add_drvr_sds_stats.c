#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_6__ {int num_sds_rings; TYPE_1__* sds; } ;
struct TYPE_7__ {TYPE_2__ hw; int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_3__ qla_host_t ;
typedef  int /*<<< orphan*/  name_str ;
struct TYPE_5__ {int /*<<< orphan*/  rx_free; int /*<<< orphan*/  intr_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_QUAD (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
qlnx_add_drvr_sds_stats(qla_host_t *ha)
{
        struct sysctl_ctx_list  *ctx;
        struct sysctl_oid_list  *children;
        struct sysctl_oid_list  *node_children;
        struct sysctl_oid       *ctx_oid;
        int                     i;
        uint8_t                 name_str[16];

        ctx = device_get_sysctl_ctx(ha->pci_dev);
        children = SYSCTL_CHILDREN(device_get_sysctl_tree(ha->pci_dev));

        ctx_oid = SYSCTL_ADD_NODE(ctx, children, OID_AUTO, "stats_drvr_sds",
                        CTLFLAG_RD, NULL, "stats_drvr_sds");
        children = SYSCTL_CHILDREN(ctx_oid);

        for (i = 0; i < ha->hw.num_sds_rings; i++) {

                bzero(name_str, (sizeof(uint8_t) * sizeof(name_str)));
                snprintf(name_str, sizeof(name_str), "%d", i);

                ctx_oid = SYSCTL_ADD_NODE(ctx, children, OID_AUTO, name_str,
                        CTLFLAG_RD, NULL, name_str);
                node_children = SYSCTL_CHILDREN(ctx_oid);

                SYSCTL_ADD_QUAD(ctx, node_children,
			OID_AUTO, "intr_count",
                        CTLFLAG_RD, &ha->hw.sds[i].intr_count,
                        "intr_count");

                SYSCTL_ADD_UINT(ctx, node_children,
			OID_AUTO, "rx_free",
                        CTLFLAG_RD, &ha->hw.sds[i].rx_free,
			ha->hw.sds[i].rx_free, "rx_free");
	}

	return;
}