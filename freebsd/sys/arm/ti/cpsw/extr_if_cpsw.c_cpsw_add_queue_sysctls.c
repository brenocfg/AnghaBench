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
struct cpsw_queue {int /*<<< orphan*/  longest_chain; int /*<<< orphan*/  queue_restart; int /*<<< orphan*/  queue_removes; int /*<<< orphan*/  queue_adds; int /*<<< orphan*/  max_avail_queue_len; int /*<<< orphan*/  avail_queue_len; int /*<<< orphan*/  max_active_queue_len; int /*<<< orphan*/  active_queue_len; int /*<<< orphan*/  queue_slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 

__attribute__((used)) static void
cpsw_add_queue_sysctls(struct sysctl_ctx_list *ctx, struct sysctl_oid *node,
	struct cpsw_queue *queue)
{
	struct sysctl_oid_list *parent;

	parent = SYSCTL_CHILDREN(node);
	SYSCTL_ADD_INT(ctx, parent, OID_AUTO, "totalBuffers",
	    CTLFLAG_RD, &queue->queue_slots, 0,
	    "Total buffers currently assigned to this queue");
	SYSCTL_ADD_INT(ctx, parent, OID_AUTO, "activeBuffers",
	    CTLFLAG_RD, &queue->active_queue_len, 0,
	    "Buffers currently registered with hardware controller");
	SYSCTL_ADD_INT(ctx, parent, OID_AUTO, "maxActiveBuffers",
	    CTLFLAG_RD, &queue->max_active_queue_len, 0,
	    "Max value of activeBuffers since last driver reset");
	SYSCTL_ADD_INT(ctx, parent, OID_AUTO, "availBuffers",
	    CTLFLAG_RD, &queue->avail_queue_len, 0,
	    "Buffers allocated to this queue but not currently "
	    "registered with hardware controller");
	SYSCTL_ADD_INT(ctx, parent, OID_AUTO, "maxAvailBuffers",
	    CTLFLAG_RD, &queue->max_avail_queue_len, 0,
	    "Max value of availBuffers since last driver reset");
	SYSCTL_ADD_UINT(ctx, parent, OID_AUTO, "totalEnqueued",
	    CTLFLAG_RD, &queue->queue_adds, 0,
	    "Total buffers added to queue");
	SYSCTL_ADD_UINT(ctx, parent, OID_AUTO, "totalDequeued",
	    CTLFLAG_RD, &queue->queue_removes, 0,
	    "Total buffers removed from queue");
	SYSCTL_ADD_UINT(ctx, parent, OID_AUTO, "queueRestart",
	    CTLFLAG_RD, &queue->queue_restart, 0,
	    "Total times the queue has been restarted");
	SYSCTL_ADD_UINT(ctx, parent, OID_AUTO, "longestChain",
	    CTLFLAG_RD, &queue->longest_chain, 0,
	    "Max buffers used for a single packet");
}