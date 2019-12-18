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
struct swrun_entry {int dummy; } ;

/* Variables and functions */
 struct swrun_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct swrun_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct swrun_entry*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  swrun_tbl ; 

void
fini_swrun_tbl(void)
{
	struct swrun_entry *n1;

	while ((n1 = TAILQ_FIRST(&swrun_tbl)) != NULL) {
		TAILQ_REMOVE(&swrun_tbl, n1, link);
		free(n1);
	}
}