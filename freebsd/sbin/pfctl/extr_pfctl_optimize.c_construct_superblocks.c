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
struct superblocks {int dummy; } ;
struct superblock {struct superblocks sb_rules; struct superblocks* sb_skipsteps; } ;
struct pfctl {int dummy; } ;
struct pf_opt_rule {struct superblocks sb_rules; struct superblocks* sb_skipsteps; } ;
struct pf_opt_queue {int dummy; } ;

/* Variables and functions */
 int PF_SKIP_COUNT ; 
 int /*<<< orphan*/  TAILQ_EMPTY (struct pf_opt_queue*) ; 
 struct superblock* TAILQ_FIRST (struct pf_opt_queue*) ; 
 int /*<<< orphan*/  TAILQ_INIT (struct superblocks*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct superblocks*,struct superblock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct pf_opt_queue*,struct superblock*,int /*<<< orphan*/ ) ; 
 struct superblock* calloc (int,int) ; 
 int /*<<< orphan*/  por_entry ; 
 int /*<<< orphan*/  sb_entry ; 
 int /*<<< orphan*/  superblock_inclusive (struct superblock*,struct superblock*) ; 
 int /*<<< orphan*/  warn (char*) ; 

int
construct_superblocks(struct pfctl *pf, struct pf_opt_queue *opt_queue,
    struct superblocks *superblocks)
{
	struct superblock *block = NULL;
	struct pf_opt_rule *por;
	int i;

	while (!TAILQ_EMPTY(opt_queue)) {
		por = TAILQ_FIRST(opt_queue);
		TAILQ_REMOVE(opt_queue, por, por_entry);
		if (block == NULL || !superblock_inclusive(block, por)) {
			if ((block = calloc(1, sizeof(*block))) == NULL) {
				warn("calloc");
				return (1);
			}
			TAILQ_INIT(&block->sb_rules);
			for (i = 0; i < PF_SKIP_COUNT; i++)
				TAILQ_INIT(&block->sb_skipsteps[i]);
			TAILQ_INSERT_TAIL(superblocks, block, sb_entry);
		}
		TAILQ_INSERT_TAIL(&block->sb_rules, por, por_entry);
	}

	return (0);
}