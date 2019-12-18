#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nitrox_softreq {int flags; struct nitrox_device* ndev; struct nitrox_cmdq* cmdq; } ;
struct TYPE_2__ {int /*<<< orphan*/  dropped; } ;
struct nitrox_device {TYPE_1__ stats; int /*<<< orphan*/  qlen; } ;
struct nitrox_cmdq {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int EINPROGRESS ; 
 int ENOSPC ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  backlog_list_add (struct nitrox_softreq*,struct nitrox_cmdq*) ; 
 int /*<<< orphan*/  cmdq_full (struct nitrox_cmdq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  post_backlog_cmds (struct nitrox_cmdq*) ; 
 int /*<<< orphan*/  post_se_instr (struct nitrox_softreq*,struct nitrox_cmdq*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nitrox_enqueue_request(struct nitrox_softreq *sr)
{
	struct nitrox_cmdq *cmdq = sr->cmdq;
	struct nitrox_device *ndev = sr->ndev;

	/* try to post backlog requests */
	post_backlog_cmds(cmdq);

	if (unlikely(cmdq_full(cmdq, ndev->qlen))) {
		if (!(sr->flags & CRYPTO_TFM_REQ_MAY_BACKLOG)) {
			/* increment drop count */
			atomic64_inc(&ndev->stats.dropped);
			return -ENOSPC;
		}
		/* add to backlog list */
		backlog_list_add(sr, cmdq);
		return -EINPROGRESS;
	}
	post_se_instr(sr, cmdq);

	return -EINPROGRESS;
}