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
struct pf_send_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_SENDQ_LOCK () ; 
 int /*<<< orphan*/  PF_SENDQ_UNLOCK () ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pf_send_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_pf_sendqueue ; 
 int /*<<< orphan*/  V_pf_swi_cookie ; 
 int /*<<< orphan*/  pfse_next ; 
 int /*<<< orphan*/  swi_sched (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pf_send(struct pf_send_entry *pfse)
{

	PF_SENDQ_LOCK();
	STAILQ_INSERT_TAIL(&V_pf_sendqueue, pfse, pfse_next);
	PF_SENDQ_UNLOCK();
	swi_sched(V_pf_swi_cookie, 0);
}