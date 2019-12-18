#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pf_ruleset {TYPE_3__* rules; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_6__ {int /*<<< orphan*/ * queues; TYPE_2__ inactive; TYPE_1__ active; } ;

/* Variables and functions */
 int PF_RULESET_MAX ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct pf_ruleset*,int /*<<< orphan*/ ,int) ; 

void
pf_init_ruleset(struct pf_ruleset *ruleset)
{
	int	i;

	memset(ruleset, 0, sizeof(struct pf_ruleset));
	for (i = 0; i < PF_RULESET_MAX; i++) {
		TAILQ_INIT(&ruleset->rules[i].queues[0]);
		TAILQ_INIT(&ruleset->rules[i].queues[1]);
		ruleset->rules[i].active.ptr = &ruleset->rules[i].queues[0];
		ruleset->rules[i].inactive.ptr = &ruleset->rules[i].queues[1];
	}
}