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
struct pf_frent {scalar_t__ fe_off; scalar_t__ fe_len; int fe_mff; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct pf_frent* TAILQ_NEXT (struct pf_frent*,int /*<<< orphan*/ ) ; 
 struct pf_frent* TAILQ_PREV (struct pf_frent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fr_next ; 
 int /*<<< orphan*/  pf_fragq ; 

__attribute__((used)) static int
pf_frent_holes(struct pf_frent *frent)
{
	struct pf_frent *prev = TAILQ_PREV(frent, pf_fragq, fr_next);
	struct pf_frent *next = TAILQ_NEXT(frent, fr_next);
	int holes = 1;

	if (prev == NULL) {
		if (frent->fe_off == 0)
			holes--;
	} else {
		KASSERT(frent->fe_off != 0, ("frent->fe_off != 0"));
		if (frent->fe_off == prev->fe_off + prev->fe_len)
			holes--;
	}
	if (next == NULL) {
		if (!frent->fe_mff)
			holes--;
	} else {
		KASSERT(frent->fe_mff, ("frent->fe_mff"));
		if (next->fe_off == frent->fe_off + frent->fe_len)
			holes--;
	}
	return holes;
}