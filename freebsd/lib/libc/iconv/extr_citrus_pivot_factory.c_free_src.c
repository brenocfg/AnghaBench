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
struct src_head {int dummy; } ;
struct src_entry {struct src_entry* se_name; int /*<<< orphan*/  se_df; } ;

/* Variables and functions */
 struct src_entry* STAILQ_FIRST (struct src_head*) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (struct src_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _db_factory_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct src_entry*) ; 
 int /*<<< orphan*/  se_entry ; 

__attribute__((used)) static void
free_src(struct src_head *sh)
{
	struct src_entry *se;

	while ((se = STAILQ_FIRST(sh)) != NULL) {
		STAILQ_REMOVE_HEAD(sh, se_entry);
		_db_factory_free(se->se_df);
		free(se->se_name);
		free(se);
	}
}