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
struct nitrox_softreq {int /*<<< orphan*/  status; int /*<<< orphan*/  backlog; } ;
struct nitrox_cmdq {int /*<<< orphan*/  backlog_qlock; int /*<<< orphan*/  backlog_count; int /*<<< orphan*/  backlog_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQ_BACKLOG ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void backlog_list_add(struct nitrox_softreq *sr,
				    struct nitrox_cmdq *cmdq)
{
	INIT_LIST_HEAD(&sr->backlog);

	spin_lock_bh(&cmdq->backlog_qlock);
	list_add_tail(&sr->backlog, &cmdq->backlog_head);
	atomic_inc(&cmdq->backlog_count);
	atomic_set(&sr->status, REQ_BACKLOG);
	spin_unlock_bh(&cmdq->backlog_qlock);
}