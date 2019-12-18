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
struct pt_section {struct pt_section* status; struct pt_section* filename; int /*<<< orphan*/  lock; int /*<<< orphan*/  alock; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct pt_section*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pt_section_free(struct pt_section *section)
{
	if (!section)
		return;

#if defined(FEATURE_THREADS)

	mtx_destroy(&section->alock);
	mtx_destroy(&section->lock);

#endif /* defined(FEATURE_THREADS) */

	free(section->filename);
	free(section->status);
	free(section);
}