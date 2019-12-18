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
struct keepdirty {int kd_extent; } ;
struct activemap {scalar_t__ am_nkeepdirty; scalar_t__ am_nkeepdirty_limit; int /*<<< orphan*/  am_keepdirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct keepdirty*,int /*<<< orphan*/ ) ; 
 struct keepdirty* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct keepdirty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kd_next ; 
 struct keepdirty* keepdirty_find (struct activemap*,int) ; 
 struct keepdirty* malloc (int) ; 
 int /*<<< orphan*/  skeepdirty ; 

__attribute__((used)) static bool
keepdirty_add(struct activemap *amp, int extent)
{
	struct keepdirty *kd;

	kd = keepdirty_find(amp, extent);
	if (kd != NULL) {
		/*
		 * Only move element at the beginning.
		 */
		TAILQ_REMOVE(&amp->am_keepdirty, kd, kd_next);
		TAILQ_INSERT_HEAD(&amp->am_keepdirty, kd, kd_next);
		return (false);
	}
	/*
	 * Add new element, but first remove the most unused one if
	 * we have too many.
	 */
	if (amp->am_nkeepdirty >= amp->am_nkeepdirty_limit) {
		kd = TAILQ_LAST(&amp->am_keepdirty, skeepdirty);
		PJDLOG_ASSERT(kd != NULL);
		TAILQ_REMOVE(&amp->am_keepdirty, kd, kd_next);
		amp->am_nkeepdirty--;
		PJDLOG_ASSERT(amp->am_nkeepdirty > 0);
	}
	if (kd == NULL)
		kd = malloc(sizeof(*kd));
	/* We can ignore allocation failure. */
	if (kd != NULL) {
		kd->kd_extent = extent;
		amp->am_nkeepdirty++;
		TAILQ_INSERT_HEAD(&amp->am_keepdirty, kd, kd_next);
	}

	return (true);
}