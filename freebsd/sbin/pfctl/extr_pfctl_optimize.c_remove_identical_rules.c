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
struct superblock {int /*<<< orphan*/  sb_rules; } ;
struct pfctl {int dummy; } ;
struct pf_rule {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;
struct pf_opt_rule {TYPE_1__ por_rule; } ;
typedef  int /*<<< orphan*/  b2 ;
typedef  int /*<<< orphan*/  a2 ;
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 int /*<<< orphan*/  DC ; 
 int /*<<< orphan*/  DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pf_opt_rule* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct pf_opt_rule* TAILQ_NEXT (struct pf_opt_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pf_opt_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comparable_rule (struct pf_rule*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exclude_supersets (struct pf_rule*,struct pf_rule*) ; 
 int /*<<< orphan*/  free (struct pf_opt_rule*) ; 
 scalar_t__ memcmp (struct pf_rule*,struct pf_rule*,int) ; 
 int /*<<< orphan*/  memcpy (struct pf_rule*,struct pf_rule*,int) ; 
 int /*<<< orphan*/  por_entry ; 

int
remove_identical_rules(struct pfctl *pf, struct superblock *block)
{
	struct pf_opt_rule *por1, *por2, *por_next, *por2_next;
	struct pf_rule a, a2, b, b2;

	for (por1 = TAILQ_FIRST(&block->sb_rules); por1; por1 = por_next) {
		por_next = TAILQ_NEXT(por1, por_entry);
		for (por2 = por_next; por2; por2 = por2_next) {
			por2_next = TAILQ_NEXT(por2, por_entry);
			comparable_rule(&a, &por1->por_rule, DC);
			comparable_rule(&b, &por2->por_rule, DC);
			memcpy(&a2, &a, sizeof(a2));
			memcpy(&b2, &b, sizeof(b2));

			exclude_supersets(&a, &b);
			exclude_supersets(&b2, &a2);
			if (memcmp(&a, &b, sizeof(a)) == 0) {
				DEBUG("removing identical rule  nr%d = *nr%d*",
				    por1->por_rule.nr, por2->por_rule.nr);
				TAILQ_REMOVE(&block->sb_rules, por2, por_entry);
				if (por_next == por2)
					por_next = TAILQ_NEXT(por1, por_entry);
				free(por2);
			} else if (memcmp(&a2, &b2, sizeof(a2)) == 0) {
				DEBUG("removing identical rule  *nr%d* = nr%d",
				    por1->por_rule.nr, por2->por_rule.nr);
				TAILQ_REMOVE(&block->sb_rules, por1, por_entry);
				free(por1);
				break;
			}
		}
	}

	return (0);
}