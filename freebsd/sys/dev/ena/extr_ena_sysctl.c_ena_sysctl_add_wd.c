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
struct ena_adapter {int /*<<< orphan*/  missing_tx_threshold; int /*<<< orphan*/  missing_tx_max_queues; int /*<<< orphan*/  missing_tx_timeout; int /*<<< orphan*/  keep_alive_timeout; int /*<<< orphan*/  wd_active; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RWTUN ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_QUAD (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_U32 (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ena_sysctl_add_wd(struct ena_adapter *adapter)
{
	device_t dev;

	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *tree;
	struct sysctl_oid_list *child;

	dev = adapter->pdev;

	ctx = device_get_sysctl_ctx(dev);
	tree = device_get_sysctl_tree(dev);
	child = SYSCTL_CHILDREN(tree);

	/* Sysctl calls for Watchdog service */
	SYSCTL_ADD_INT(ctx, child, OID_AUTO, "wd_active",
	    CTLFLAG_RWTUN, &adapter->wd_active, 0,
	    "Watchdog is active");

	SYSCTL_ADD_QUAD(ctx, child, OID_AUTO, "keep_alive_timeout",
	    CTLFLAG_RWTUN, &adapter->keep_alive_timeout,
	    "Timeout for Keep Alive messages");

	SYSCTL_ADD_QUAD(ctx, child, OID_AUTO, "missing_tx_timeout",
	    CTLFLAG_RWTUN, &adapter->missing_tx_timeout,
	    "Timeout for TX completion");

	SYSCTL_ADD_U32(ctx, child, OID_AUTO, "missing_tx_max_queues",
	    CTLFLAG_RWTUN, &adapter->missing_tx_max_queues, 0,
	    "Number of TX queues to check per run");

	SYSCTL_ADD_U32(ctx, child, OID_AUTO, "missing_tx_threshold",
	    CTLFLAG_RWTUN, &adapter->missing_tx_threshold, 0,
	    "Max number of timeouted packets");
}