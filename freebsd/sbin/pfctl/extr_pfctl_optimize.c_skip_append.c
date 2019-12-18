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
struct superblock {int /*<<< orphan*/ * sb_skipsteps; } ;
struct pf_skip_step {scalar_t__ ps_count; int /*<<< orphan*/  ps_rules; } ;
struct pf_opt_rule {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_BEFORE (struct pf_skip_step*,struct pf_skip_step*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pf_opt_rule*,int /*<<< orphan*/ ) ; 
 struct pf_skip_step* TAILQ_PREV (struct pf_skip_step*,struct pf_skip_step*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pf_skip_step*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * por_skip_entry ; 
 int /*<<< orphan*/  ps_entry ; 

void
skip_append(struct superblock *superblock, int skipnum,
    struct pf_skip_step *skiplist, struct pf_opt_rule *por)
{
	struct pf_skip_step *prev;

	skiplist->ps_count++;
	TAILQ_INSERT_TAIL(&skiplist->ps_rules, por, por_skip_entry[skipnum]);

	/* Keep the list of skiplists sorted by whichever is larger */
	while ((prev = TAILQ_PREV(skiplist, skiplist, ps_entry)) &&
	    prev->ps_count < skiplist->ps_count) {
		TAILQ_REMOVE(&superblock->sb_skipsteps[skipnum],
		    skiplist, ps_entry);
		TAILQ_INSERT_BEFORE(prev, skiplist, ps_entry);
	}
}