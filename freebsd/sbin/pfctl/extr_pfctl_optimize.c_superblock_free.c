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
struct superblock {struct superblock* sb_profiled_block; struct superblock* por_dst_tbl; struct superblock* pt_buf; struct superblock* por_src_tbl; int /*<<< orphan*/  sb_rules; } ;
struct pfctl {int dummy; } ;
struct pf_opt_rule {struct pf_opt_rule* sb_profiled_block; struct pf_opt_rule* por_dst_tbl; struct pf_opt_rule* pt_buf; struct pf_opt_rule* por_src_tbl; int /*<<< orphan*/  sb_rules; } ;

/* Variables and functions */
 struct superblock* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct superblock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct superblock*) ; 
 int /*<<< orphan*/  pfr_buf_clear (struct superblock*) ; 
 int /*<<< orphan*/  por_entry ; 

void
superblock_free(struct pfctl *pf, struct superblock *block)
{
	struct pf_opt_rule *por;
	while ((por = TAILQ_FIRST(&block->sb_rules))) {
		TAILQ_REMOVE(&block->sb_rules, por, por_entry);
		if (por->por_src_tbl) {
			if (por->por_src_tbl->pt_buf) {
				pfr_buf_clear(por->por_src_tbl->pt_buf);
				free(por->por_src_tbl->pt_buf);
			}
			free(por->por_src_tbl);
		}
		if (por->por_dst_tbl) {
			if (por->por_dst_tbl->pt_buf) {
				pfr_buf_clear(por->por_dst_tbl->pt_buf);
				free(por->por_dst_tbl->pt_buf);
			}
			free(por->por_dst_tbl);
		}
		free(por);
	}
	if (block->sb_profiled_block)
		superblock_free(pf, block->sb_profiled_block);
	free(block);
}