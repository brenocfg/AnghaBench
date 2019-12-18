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
struct vtscsi_statistics {int /*<<< orphan*/  dequeue_no_requests; int /*<<< orphan*/  scsi_cmd_timeouts; } ;
struct vtscsi_softc {int /*<<< orphan*/  vtscsi_debug; struct vtscsi_statistics vtscsi_stats; int /*<<< orphan*/  vtscsi_dev; } ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_ULONG (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtscsi_add_sysctl(struct vtscsi_softc *sc)
{
	device_t dev;
	struct vtscsi_statistics *stats;
        struct sysctl_ctx_list *ctx;
	struct sysctl_oid *tree;
	struct sysctl_oid_list *child;

	dev = sc->vtscsi_dev;
	stats = &sc->vtscsi_stats;
	ctx = device_get_sysctl_ctx(dev);
	tree = device_get_sysctl_tree(dev);
	child = SYSCTL_CHILDREN(tree);

	SYSCTL_ADD_INT(ctx, child, OID_AUTO, "debug_level",
	    CTLFLAG_RW, &sc->vtscsi_debug, 0,
	    "Debug level");

	SYSCTL_ADD_ULONG(ctx, child, OID_AUTO, "scsi_cmd_timeouts",
	    CTLFLAG_RD, &stats->scsi_cmd_timeouts,
	    "SCSI command timeouts");
	SYSCTL_ADD_ULONG(ctx, child, OID_AUTO, "dequeue_no_requests",
	    CTLFLAG_RD, &stats->dequeue_no_requests,
	    "No available requests to dequeue");
}