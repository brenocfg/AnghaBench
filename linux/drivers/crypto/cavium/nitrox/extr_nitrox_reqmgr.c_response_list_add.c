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
struct nitrox_softreq {int /*<<< orphan*/  response; } ;
struct nitrox_cmdq {int /*<<< orphan*/  resp_qlock; int /*<<< orphan*/  response_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void response_list_add(struct nitrox_softreq *sr,
				     struct nitrox_cmdq *cmdq)
{
	INIT_LIST_HEAD(&sr->response);

	spin_lock_bh(&cmdq->resp_qlock);
	list_add_tail(&sr->response, &cmdq->response_head);
	spin_unlock_bh(&cmdq->resp_qlock);
}