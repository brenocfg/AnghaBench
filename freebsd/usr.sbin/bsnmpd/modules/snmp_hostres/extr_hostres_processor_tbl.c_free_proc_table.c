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
struct processor_entry {int dummy; } ;

/* Variables and functions */
 struct processor_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct processor_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ detected_processor_count ; 
 int /*<<< orphan*/  free (struct processor_entry*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  processor_tbl ; 

__attribute__((used)) static void
free_proc_table(void)
{
	struct processor_entry *n1;

	while ((n1 = TAILQ_FIRST(&processor_tbl)) != NULL) {
		TAILQ_REMOVE(&processor_tbl, n1, link);
		free(n1);
		detected_processor_count--;
	}

	assert(detected_processor_count == 0);
	detected_processor_count = 0;
}