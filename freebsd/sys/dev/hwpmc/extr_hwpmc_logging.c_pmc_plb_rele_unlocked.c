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
struct pmclog_buffer {size_t plb_domain; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdbh_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct pmclog_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plb_next ; 
 TYPE_1__** pmc_dom_hdrs ; 

__attribute__((used)) static inline void
pmc_plb_rele_unlocked(struct pmclog_buffer *plb)
{
	TAILQ_INSERT_HEAD(&pmc_dom_hdrs[plb->plb_domain]->pdbh_head, plb, plb_next);
}