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
struct nitrox_cmdq {int /*<<< orphan*/  resp_qlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void response_list_del(struct nitrox_softreq *sr,
				     struct nitrox_cmdq *cmdq)
{
	spin_lock_bh(&cmdq->resp_qlock);
	list_del(&sr->response);
	spin_unlock_bh(&cmdq->resp_qlock);
}