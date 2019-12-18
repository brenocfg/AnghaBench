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
struct pt_section {int ucount; int /*<<< orphan*/  lock; int /*<<< orphan*/  alock; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct pt_section*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int pt_section_lock (struct pt_section*) ; 
 int pt_section_unlock (struct pt_section*) ; 
 int pte_internal ; 

int pt_section_put(struct pt_section *section)
{
	int errcode, ucount;

	if (!section)
		return -pte_internal;

	errcode = pt_section_lock(section);
	if (errcode < 0)
		return errcode;

	ucount = --section->ucount;

	errcode = pt_section_unlock(section);
	if (errcode < 0)
		return errcode;

	if (!ucount) {
#if defined(FEATURE_THREADS)
		mtx_destroy(&section->alock);
		mtx_destroy(&section->lock);
#endif /* defined(FEATURE_THREADS) */
		free(section);
	}

	return 0;
}