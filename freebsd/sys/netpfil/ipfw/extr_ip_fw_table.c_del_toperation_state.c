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
struct tables_config {int /*<<< orphan*/  state_list; } ;
struct tableop_state {int /*<<< orphan*/  opstate; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 struct tables_config* CHAIN_TO_TCFG (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 

void
del_toperation_state(struct ip_fw_chain *ch, struct tableop_state *ts)
{
	struct tables_config *tcfg;

	tcfg = CHAIN_TO_TCFG(ch);
	TAILQ_REMOVE(&tcfg->state_list, &ts->opstate, next);
}